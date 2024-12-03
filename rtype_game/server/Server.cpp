/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include "../../ecs/udp/UDP_Manager.hpp"

namespace rtype {

    Server::Server() : _running(true), _currentPort(5000)
    {
        std::cout << "START OF THE RTYPE SERVER" << std::endl;
        initializeCommands();
    }

    Server::~Server()
    {
        std::cout << "STOP OF THE RTYPE SERVER" << std::endl;
    }

    void Server::initializeCommands() {
        _commands[RTYPE_ACTIONS::CREATE_ROOM] = [this](const unsigned int id, std::string& params, std::string& body, std::string& clientAddr) {
            createRoom(id, params, body, clientAddr);
        };
        _commands[RTYPE_ACTIONS::JOIN_ROOM] = [this](const unsigned int id, std::string& params, std::string& body, std::string& clientAddr) {
            joinRoom(id, params, body, clientAddr);
        };
        _commands[RTYPE_ACTIONS::EXIT] = [this](const unsigned int id, std::string& params, std::string& body, std::string& clientAddr) { // FOR DEVELOPMENT ONLY, REMOVE BEFORE DELIVERY
            (void)id;
            (void)params;
            (void)body;
            (void)clientAddr;
            setRunning(false);
        };
    }

    void Server::handleCommand(const std::vector<char>& message, std::string clientAddr) {
        ecs::udp::Message mes;
        _compressor.deserialize(message, mes);
        _mes_checker.checkAction(mes);
        std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << " body " << mes.body << std::endl;
        auto it = _commands.find(mes.action);
        if (it != _commands.end()) {
            it->second(mes.id, mes.params, mes.body, clientAddr);
        } else {
            throw ERROR::InvalidActionExceptions("Invalid action");
        }
    }

    bool Server::isRunning() const
    {
        return this->_running;
    }

    void Server::setRunning(bool running)
    {
        this->_running = running;
    }

    int Server::start()
    {
        if (!_udpManager.initialize("rtype_game/config/udp_config.conf")) {
            std::cerr << "Server initialization failed." << std::endl;
            return 1;
        }

        std::vector<char> message;
        while (isRunning()) {
            if (_udpManager.receiveMessage(message)) {
                try {
                    handleCommand(message, _udpManager.getLastClientAddress());
                } catch (std::exception &e) {
                    std::cerr << std::endl << e.what() << std::endl;
                }
            }
        }
        return 0;
    }

    void Server::createRoom(const unsigned int id, std::string& params, std::string& body, std::string& lastclientAdr) {

        (void)id;
        (void)body;
        // Je check les params de la room et du client

        std::map<std::string, std::string> map_params = _mes_checker.checkFormatParams(params);

        checkCreateRoomArgs(map_params);

        Room newRoom(_currentPort, map_params["room_name"]);
        _rooms.push_back(std::move(newRoom));
        _rooms.back().start(_currentPort);
        _currentPort++;

        // Je notifie la room du nouveau client

        for (auto& room : _rooms) {
            if (room.getName() == map_params["room_name"]) {
                room.createClient(lastclientAdr);
            }
        }
    }

    void Server::joinRoom(const unsigned int id, std::string& params, std::string& body, std::string& lastclientAdr) {

        (void)id;
        (void)body;

        // Je check les params de la room et du client

        std::map<std::string, std::string> map_params = _mes_checker.checkFormatParams(params);

        checkJoinRoomArgs(map_params);

        // Je notifie la room du nouveau client

        for (auto& room : _rooms) {
            if (room.getName() == map_params["room_name"]) {
                room.createClient(lastclientAdr);
            }
        }
    }

    void Server::checkCreateRoomArgs(std::map<std::string, std::string> params) {
        if (params.find("room_name") == params.end() || params.find("client_name") == params.end())
            throw ERROR::MissingRoomsParamsExceptions("Missing 'room_name' param or 'client_name' param");

        for (const Room& room : _rooms) {
            if (room.getName() == params["room_name"]) {
                throw ERROR::RoomAlreadyExistingExceptions("This name is already taken for a room");
            }
        }
    }

    void Server::checkJoinRoomArgs(std::map<std::string, std::string> params) {
        if (params.find("room_name") == params.end() || params.find("client_name") == params.end())
            throw ERROR::MissingRoomsParamsExceptions("Missing 'room_name' param or 'client_name' param");


        bool roomFound = false;

        for (const Room& room : _rooms) {
            if (room.getName() == params["room_name"]) {
                roomFound = true;
                if (room.getNbClient() >= 4) {
                    throw ERROR::RoomIsFullExceptions("The room is full of client (4 MAX PER ROOM)");
                }
            }
        }

        if (!roomFound) {
            throw ERROR::RoomNotFoundExceptions("Room not found");
        }
    }
}