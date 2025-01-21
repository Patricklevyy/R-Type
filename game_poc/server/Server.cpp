/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"

namespace poc_game
{

    Server::Server()
        : _running(true), _currentPort(5000),
          _udpManager(std::make_shared<ecs::udp::UDP_Manager>())
    {
        std::cout << "START OF THE RTYPE SERVER" << std::endl;
        initializeCommands();
    }

    Server::~Server()
    {
        _udpManager->stopReceiving();
        std::cout << "STOP OF THE RTYPE SERVER" << std::endl;
    }

    void Server::initializeCommands()
    {
        _commands[POC_GAME_ACTIONS::START] = [this](const unsigned int id,
                                                 std::string &params,
                                                 std::string &clientAddr) {
            (void) id;
            start_game(clientAddr, params);
        };
    }

    void Server::start_game(const std::string &clientAddr, std::string &params)
    {
        std::map<std::string, std::string> map_params =
            Utils::parseMessageParams(params);

        std::string room_name = "ROOM " + std::to_string(_rooms_nb);
        auto newRoom = std::make_shared<Room>(_currentPort, room_name);
        _rooms.push_back(std::move(newRoom));
        _rooms.back()->start(
            _currentPort, map_params["x"], map_params["y"], clientAddr);
        _currentPort++;
        _rooms_nb++;
    }

    void Server::handleCommand(
        const std::vector<char> &message, std::string clientAddr)
    {
        ecs::udp::Message mes;
        _compressor.deserialize(message, mes);
        if (!SecretKeyChecker::isMessageSafe(
                mes.secret_key, _udpManager->getSecretKey())) {
            throw ERROR::MessageIsNotSafeException("Missing secret key");
        }
        Utils::checkAction(mes.action);
        std::cout << "id : " << mes.id << " action " << mes.action << " params "
                  << mes.params << std::endl;
        auto it = _commands.find(mes.action);
        if (it != _commands.end()) {
            it->second(mes.id, mes.params, clientAddr);
        } else {
            throw ERROR::InvalidActionExceptions("Invalid action in Server");
        }
    }

    void Server::start()
    {
        if (!_udpManager->initialize("game_poc/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeServerExceptions(
                "Failed to start the server.");
        }
        _timer.init("rtype_game/config/server_config.conf", true);

        std::vector<char> message;
        _udpManager->startReceiving();
        while (_running) {
            _timer.waitTPS();
            auto messages = _udpManager->fetchAllMessages();
            for (auto &[clientAddress, message] : messages) {
                try {
                    handleCommand(message, clientAddress);
                } catch (std::exception &e) {
                    std::cerr << std::endl << e.what() << std::endl;
                }
            }
        }
    }
} // namespace poc_game