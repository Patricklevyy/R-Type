/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Send_Message
*/

#include "Client.hpp"

namespace poc_game
{
    void Client::send_server_playing()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = POC_GAME_ACTIONS::PLAY;
        mess.secret_key = _udpClient->getSecretKey();

        _message_compressor.serialize(mess, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::send_server_jump()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = POC_GAME_ACTIONS::JUMP;
        mess.secret_key = _udpClient->getSecretKey();

        _message_compressor.serialize(mess, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::send_server_start_game()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = POC_GAME_ACTIONS::START;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "x=" + std::to_string(_window_width)
            + ";y=" + std::to_string(_window_height);

        _message_compressor.serialize(mess, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::send_server_restart_game()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = POC_GAME_ACTIONS::RESTART;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "x=" + std::to_string(_window_width)
            + ";y=" + std::to_string(_window_height);

        _message_compressor.serialize(mess, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }
} // namespace poc_game
