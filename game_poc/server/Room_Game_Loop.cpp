/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Game_Loop
*/

#include "Room.hpp"

namespace poc_game
{
    void Room::create_client(std::string lastclientAdr)
    {
        std::cout << "Client created in room [" << _name << "] with addr: " << lastclientAdr << std::endl;

        std::string roomAddress = getAddress();

        std::pair<float, float> position(_window_width / 3, _window_height / 2);

        std::vector<char> send_message;
        ecs::udp::Message mes;
        mes.action = POC_GAME_ACTIONS::CREATE_CLIENT;
        mes.params = std::to_string(static_cast<int>(position.first)) + ";" + std::to_string(static_cast<int>(position.second)) + ";" + std::to_string(_port);

        std::cout << "CREATE CLINET : " << mes.params << std::endl;
        mes.id = create_player(position);
        _message_compressor.serialize(mes, send_message);
        _clientAddresses.push_back(lastclientAdr);
        std::cout << lastclientAdr << std::endl;
        if (_udp_server->sendMessage(send_message, lastclientAdr)) {

            std::cout << "Message sent: " << mes.params << std::endl;
        } else {
            std::cerr << "Failed to send message." << std::endl;
        }
    }

    void Room::handleCommand(const std::vector<char> &compressed_message, std::string clientAddr)
    {
        (void)clientAddr;
        ecs::udp::Message message;
        _message_compressor.deserialize(compressed_message, message);
        std::cout << "new message in the ROOOM : " << message.id << "action : " << message.action << " , " << message.params << std::endl;
        POC_GAME_ACTIONS action = static_cast<POC_GAME_ACTIONS>(message.action);
        _eventBus.emit(action, std::ref(message));
    }

    void Room::gameThreadFunction(int port, std::string window_width, std::string window_height, std::string clientAddr)
    {
        _window_width = std::stoi(window_width);
        _window_height = std::stoi(window_height);
        _port = port;
        _udp_server = std::make_shared<ecs::udp::UDP_Server>();

        if (!_udp_server->initialize("game_poc/config/udp_config.conf", port)) {
            std::cerr << "Failed to initialize socket for room " << _name << std::endl;
            return;
        }
        _ecs.init_basic_registry();
        init_ecs_server_registry();
        _udp_server->startReceiving();
        _timer.init("game_poc/config/server_config.conf", true);
        _game_running = true;
        std::cout << "je suis dans le game thread" << std::endl;
        init_event_bus();
        create_client(clientAddr);

        while (_game_running) {
            _timer.waitTPS();
            _eventBus.emit(POC_GAME_ACTIONS::EXECUTE_GRAVITY);
            _eventBus.emit(POC_GAME_ACTIONS::UPDATE_POSITIONS);
            _eventBus.emit(POC_GAME_ACTIONS::CHECK_OFF_SCREEN);
            auto messages = _udp_server->fetchAllMessages();
            if (messages.size() != 0) {
                for (const auto &[clientAddress, message] : messages) {
                    handleCommand(message, clientAddress);
                }
            }
            _eventBus.emit(POC_GAME_ACTIONS::CHECK_COLLISIONS);
            if (isPlaying)
                spawn_pipes();
            send_client_positions_update();
        }
        _udp_server->stopReceiving();
    }

    void Room::start(int port, std::string window_width, std::string window_height, std::string clientAddr)
    {
        std::cout << "j'inite et je creer les threads" << std::endl;
        _gameThread = std::thread(&Room::gameThreadFunction, this, port, window_width, window_height, clientAddr);
        _gameThread.detach();
    }
}