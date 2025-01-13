/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Game_Loop
*/

#include "Room.hpp"

namespace rtype
{
    void Room::gameThreadFunction(int port, std::string window_width, std::string window_height, std::string difficulty)
    {
        init_all(port, window_width, window_height, difficulty);

        auto lastClientUpdate = std::chrono::steady_clock::now();

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
            auto currentTime = std::chrono::steady_clock::now();
            auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastClientUpdate);

            if (elapsedTime.count() >= 2) {
                send_roll_back();
                lastClientUpdate = currentTime;
            }
            _eventBus.emit(RTYPE_ACTIONS::CHECK_COLLISIONS);
            _eventBus.emit(RTYPE_ACTIONS::CHECK_LIFES);
            _eventBus.emit(RTYPE_ACTIONS::EXECUTE_LEVEL);
            _eventBus.emit(RTYPE_ACTIONS::CHECK_LEVEL_FINISHED);
            _eventBus.emit(RTYPE_ACTIONS::SPAWN_ASTEROIDE);
            send_client_positions_update();
        }
        _udp_server->stopReceiving();
    }

    void Room::start(int port, std::string window_width, std::string window_height, std::string difficulty)
    {
        std::cout << "j'inite et je creer les threads" << std::endl;
        _gameThread = std::thread(&Room::gameThreadFunction, this, port, window_width, window_height, difficulty);
        _gameThread.detach();
    }
}