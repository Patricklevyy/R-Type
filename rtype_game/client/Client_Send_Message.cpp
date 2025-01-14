/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Send_Message
*/

#include "Client.hpp"

namespace rtype
{
    void Client::send_server_new_shoot(bool charged)
    {
        ecs::udp::Message message;
        std::vector<char> buffer;
        std::pair<float, float> player_positions =
            _position_system.getPlayerPosition(
                _player_system.getIndexPlayer(_ecs._components_arrays),
                _ecs._components_arrays);

        message.id = 0;
        message.action = RTYPE_ACTIONS::CREATE_PROJECTILE;
        message.secret_key = _udpClient->getSecretKey();
        message.params =
            "x=" + std::to_string(player_positions.first + 100) + ";y=";
        if (!charged) {
            message.params += std::to_string(player_positions.second + 20);
        } else {
            message.params += std::to_string(player_positions.second - 20);
        }
        message.params += std::to_string(player_positions.second + 20);
        message.params += ";dir_x=" + std::to_string(ecs::direction::RIGHT)
            + ";dir_y=" + std::to_string(ecs::direction::NO_DIRECTION);
        if (!charged) {
            message.params +=
                ";type=" + std::to_string(SPRITES::PLAYER_SIMPLE_MISSILE);
        } else {
            message.params +=
                ";type=" + std::to_string(SPRITES::PLAYER_CHARGED_SHOOT);
        }

        _message_compressor.serialize(message, buffer);

        _udpClient->sendMessageToDefault(buffer);
    }

    void Client::send_server_player_direction(
        ecs::direction x, ecs::direction y)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = ecs_client_to_server[_player_system.getIndexPlayer(
            _ecs._components_arrays)];
        ;
        mess.action = RTYPE_ACTIONS::UPDATE_DIRECTION;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "x=" + std::to_string(x) + ";y=" + std::to_string(y);

        _message_compressor.serialize(mess, buffer);

        _udpClient->sendMessageToDefault(buffer);
    }

    void Client::send_server_start_game(LEVELS level)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = level;
        mess.action = RTYPE_ACTIONS::START_LEVEL;
        mess.secret_key = _udpClient->getSecretKey();
        _message_compressor.serialize(mess, buffer);

        _udpClient->sendMessageToDefault(buffer);
    }

    void Client::send_server_create_room(std::string roomName)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = 0;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "room_name=" + roomName
            + ";x=" + std::to_string(_window_width)
            + ";y=" + std::to_string(_window_height)
            + ";dif=" + std::to_string(_difficulty);

        _message_compressor.serialize(mess, buffer);

        _udpClient->sendMessageToDefault(buffer);
        requestRoomList();
    }

    void Client::send_server_join_room(
        std::string roomName, std::string clientName)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 1;
        mess.action = 1;
        mess.secret_key = _udpClient->getSecretKey();
        mess.params = "room_name=" + roomName + ";client_name=" + clientName
            + ";x=" + std::to_string(_window_width)
            + ";y=" + std::to_string(_window_height);

        _message_compressor.serialize(mess, buffer);

        _udpClient->sendMessageToDefault(buffer);
        requestRoomList();
    }

    void Client::send_server_new_player()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = RTYPE_ACTIONS::CREATE_PLAYER;
        mess.secret_key = _udpClient->getSecretKey();
        _message_compressor.serialize(mess, buffer);

        _udpClient->sendMessageToDefault(buffer);
    }

    void Client::requestRoomList()
    {
        // std::cout << "J'ai demandé au serveur avant les rooms" << std::endl;
        ecs::udp::Message request;
        request.id = 0;
        request.action = RTYPE_ACTIONS::GET_ALL_ROOMS;
        request.secret_key = _udpClient->getSecretKey();
        request.params = "";
        std::vector<char> buffer;
        _message_compressor.serialize(request, buffer);
        _udpClient->sendMessageToDefault(buffer);
        // std::cout << "Room list updated: " << _roomsList.size()
        //           << " rooms found." << std::endl;
    }
} // namespace rtype
