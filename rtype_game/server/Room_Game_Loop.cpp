/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Game_Loop
*/

#include "Room.hpp"

namespace rtype
{
    void Room::gameThreadFunction(int port, std::string window_width, std::string window_height)
    {
        _window_width = std::stoi(window_width);
        _window_height = std::stoi(window_height);
        _port = port;
        _udp_server = std::make_shared<ecs::udp::UDP_Server>();
        _gampeplay_factory = std::make_shared<GameplayFactory>();

        _gampeplay_factory->init("rtype_game/config/gameplay_config.conf");

        if (!_udp_server->initialize("rtype_game/config/udp_config.conf", port)) {
            std::cerr << "Failed to initialize socket for room " << _name << std::endl;
            return;
        }
        _ecs.init_basic_registry();
        init_ecs_server_registry();
        _udp_server->startReceiving();
        _timer.init("rtype_game/config/server_config.conf", true);
        _game_running = true;
        std::cout << "je suis dans le game thread" << std::endl;
        init_event_bus();

        while (_game_running) {
            _timer.waitTPS();
            _eventBus.emit(RTYPE_ACTIONS::UPDATE_POSITIONS);
            _eventBus.emit(RTYPE_ACTIONS::MOVE_MONSTERS);
            _eventBus.emit(RTYPE_ACTIONS::CHECK_OFF_SCREEN);
            _eventBus.emit(RTYPE_ACTIONS::ENEMY_SHOOT);
            auto messages = _udp_server->fetchAllMessages();
            if (messages.size() != 0) {
                for (const auto &[clientAddress, message] : messages) {
                    handleCommand(message, clientAddress);
                }
            }
            _eventBus.emit(RTYPE_ACTIONS::CHECK_COLLISIONS);
            _eventBus.emit(RTYPE_ACTIONS::CHECK_LIFES);
            _eventBus.emit(RTYPE_ACTIONS::EXECUTE_LEVEL);
            _eventBus.emit(RTYPE_ACTIONS::CHECK_LEVEL_FINISHED);
            send_client_positions_update();
        }
        _udp_server->stopReceiving();
    }

    void Room::start(int port, std::string window_width, std::string window_height)
    {
        std::cout << "j'inite et je creer les threads" << std::endl;
        _gameThread = std::thread(&Room::gameThreadFunction, this, port, window_width, window_height);
        _gameThread.detach();
    }
}