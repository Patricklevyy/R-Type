/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"

namespace rtype
{

    Server::Server()
        : _running(true), _currentPort(5000), _udpManager(std::make_shared<ecs::udp::UDP_Manager>())
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
        _commands[RTYPE_ACTIONS::CREATE_ROOM] = [this](const unsigned int id, std::string &params, std::string &clientAddr) {
            createRoom(id, params, clientAddr);
        };
        _commands[RTYPE_ACTIONS::JOIN_ROOM] = [this](const unsigned int id, std::string &params, std::string &clientAddr) {
            joinRoom(id, params, clientAddr);
        };
        _commands[RTYPE_ACTIONS::GET_ALL_ROOMS] = [this](const unsigned int id, std::string &params, std::string &clientAddr) {
            (void)id;
            (void)params;

            getAllRooms(clientAddr);
        };
    }

    void Server::getAllRooms(std::string &clientAddr)
    {
        std::string roomList = "rooms=";
        for (const auto &room : _rooms) {
            roomList += room.getName() + "," + std::to_string(room.getNbClient()) + ":";
        }
        if (!roomList.empty() && roomList.back() == ':') {
            roomList.pop_back();
        }
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::GET_ALL_ROOMS;
        responseMessage.id = 0;
        responseMessage.params = roomList;
        _compressor.serialize(responseMessage, response);
        _udpManager->sendMessage(response, clientAddr);
    }

    void Server::handleCommand(const std::vector<char> &message, std::string clientAddr)
    {
        ecs::udp::Message mes;
        _compressor.deserialize(message, mes);
        if (!SecretKeyChecker::isMessageSafe(mes.secret_key, _udpManager->getSecretKey())) {
            throw ERROR::MessageIsNotSafeException("Missiing secret key");
        }
        _mes_checker.checkAction(mes);
        _mes_checker.checkFormatParams(mes.params);
        std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << std::endl;
        auto it = _commands.find(mes.action);
        if (it != _commands.end()) {
            it->second(mes.id, mes.params, clientAddr);
        } else {
            throw ERROR::InvalidActionExceptions("Invalid action");
        }
    }

    void Server::start()
    {
        if (!_udpManager->initialize("rtype_game/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeServerExceptions("Failed to start the server.");
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
                    std::cerr << std::endl
                              << e.what() << std::endl;
                }
            }
        }
    }
}