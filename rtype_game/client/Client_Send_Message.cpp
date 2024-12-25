/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Send_Message
*/

#include "Client.hpp"

namespace rtype
{
    void Client::send_server_new_shoot()
    {
        ecs::udp::Message message;
        std::vector<char> buffer;
        std::pair<float, float> player_positions = _position_system.getPlayerPosition(_player_system.getIndexPlayer(_ecs._components_arrays), _ecs._components_arrays);

        message.id = 0;
        message.action = RTYPE_ACTIONS::PLAYER_SHOOT;
        message.secret_key = _udpClient->getSecretKey();
        message.params = "x=" + std::to_string(player_positions.first + 100) + ";y=" + std::to_string(player_positions.second + 20) + ";dir_x=" + std::to_string(ecs::direction::RIGHT) + ";dir_y=" + std::to_string(ecs::direction::NO_DIRECTION) + ";type=" + std::to_string(SPRITES::PLAYER_SIMPLE_MISSILE);

        _message_compressor.serialize(message, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::send_server_player_direction(ecs::direction x, ecs::direction y)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = ecs_client_to_server[_player_system.getIndexPlayer(_ecs._components_arrays)];
        ;
        mess.action = RTYPE_ACTIONS::UPDATE_DIRECTION;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "x=" + std::to_string(x) + ";y=" + std::to_string(y);

        _message_compressor.serialize(mess, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::send_server_start_game(LEVELS level)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = level;
        mess.action = RTYPE_ACTIONS::START_LEVEL;
        mess.secret_key = _udpClient->getSecretKey();
        _message_compressor.serialize(mess, buffer);

        std::cout << "je send" << std::endl;
        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::send_server_create_room()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = 0;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "room_name=room1;x=" + std::to_string(_window_width) + ";y=" + std::to_string(_window_height);

        _message_compressor.serialize(mess, buffer);

        std::cout << "je send" << std::endl;
        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::send_server_join_room()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 1;
        mess.action = 1;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "room_name=room1;client_name=patrick;x=" + std::to_string(_window_width) + ";y=" + std::to_string(_window_height);

        _message_compressor.serialize(mess, buffer);

        std::cout << "je send" << std::endl;
        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }
}
