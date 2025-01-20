/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Send_Message
*/

#include "Room.hpp"

namespace poc_game
{
    void Room::send_client_dead_entities(std::list<size_t> dead_entities_id)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = POC_GAME_ACTIONS::KILL_ENTITY;
        responseMessage.id = 0;

        std::string ids;
        for (const auto &id : dead_entities_id) {
            if (!ids.empty()) {
                ids += ";";
            }
            ids += std::to_string(id);
        }

        responseMessage.params = ids;
        std::cout << "DEAD ENTITIES : " << responseMessage.params << std::endl;

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_positions_update()
    {
        std::string updateMessage = "";

        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(
            _ecs._components_arrays[typeid(ecs::Position)]);

        for (size_t i = 0; i < positions.size(); ++i) {
            if (positions[i].has_value()) {
                updateMessage += std::to_string(i) + ","
                    + std::to_string(
                        static_cast<int>(round(positions[i].value()._pos_x)))
                    + ","
                    + std::to_string(
                        static_cast<int>(round(positions[i].value()._pos_y)))
                    + ";";
            }
        }

        if (!updateMessage.empty() && updateMessage.back() == ';') {
            updateMessage.pop_back();
        }

        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = POC_GAME_ACTIONS::UPDATE_POSITIONS_FROM_SERVER;
        responseMessage.id = 0;
        responseMessage.params = updateMessage;

        _message_compressor.serialize(responseMessage, response);
        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_loose_game()
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = POC_GAME_ACTIONS::FAIL_LEVEL;
        responseMessage.id = 0;

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_create_player()
    {
        std::string roomAddress = getAddress();

        std::pair<float, float> position(_window_width / 3, _window_height / 2);

        std::vector<char> send_message;
        ecs::udp::Message mes;
        mes.action = POC_GAME_ACTIONS::CREATE_PLAYER;
        mes.params = std::to_string(static_cast<int>(position.first)) + ";"
            + std::to_string(static_cast<int>(position.second)) + ";"
            + std::to_string(_port);

        std::cout << "CREATE CLINET : " << mes.params << std::endl;
        mes.id = create_player(position);
        _message_compressor.serialize(mes, send_message);
        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(send_message, clientAddr);
        }
    }

    void Room::send_client_new_pipe(
        size_t index, float x, float y, SPRITES sprite)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = POC_GAME_ACTIONS::SPAWN_PIPE;
        responseMessage.id = index;

        responseMessage.params = "x=" + std::to_string(x)
            + ";y=" + std::to_string(y) + ";type=" + std::to_string(sprite);

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }
} // namespace poc_game