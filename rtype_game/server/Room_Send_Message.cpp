/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Send_Message
*/

#include "Room.hpp"

namespace rtype
{
    void Room::sendScore(unsigned int score)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;

        responseMessage.id = 0;
        responseMessage.action = UPDATE_SCORE;
        responseMessage.params = std::to_string(score);

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_level_status(bool win, LEVELS level)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;

        responseMessage.id = 0;
        if (win) {
            responseMessage.action = RTYPE_ACTIONS::WIN_LEVEL;
            responseMessage.params = std::to_string(level);
        } else {
            responseMessage.action = RTYPE_ACTIONS::FAIL_LEVEL;
        }

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_dead_entities(std::list<size_t> dead_entities_id)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::KILL_ENTITY;
        responseMessage.id = 0;

        std::string ids;
        for (const auto &id : dead_entities_id) {
            if (!ids.empty()) {
                ids += ";";
            }
            ids += std::to_string(id);
        }

        responseMessage.params = ids;

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_new_projectile(size_t index_ecs_server, std::string &params)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::CREATE_PROJECTILE;
        responseMessage.id = index_ecs_server;
        responseMessage.params = params;

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_positions_update()
    {
        std::string updateMessage = "";

        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(_ecs._components_arrays[typeid(ecs::Position)]);
        auto &healths = std::any_cast<ecs::SparseArray<Health> &>(_ecs._components_arrays[typeid(Health)]);
        auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(_ecs._components_arrays[typeid(Monster)]);
        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(_ecs._components_arrays[typeid(ecs::Playable)]);

        for (size_t i = 0; i < positions.size(); ++i) {
            if ((positions[i].has_value() && i < healths.size() && healths[i].has_value()) && ((i < monsters.size() && monsters[i].has_value()) || (i < playables.size() && playables[i].has_value()))) {
                updateMessage += std::to_string(i) +
                                "," + std::to_string(static_cast<int>(round(positions[i].value()._pos_x))) +
                                "," + std::to_string(static_cast<int>(round(positions[i].value()._pos_y))) + ";";
            }
        }

        if (!updateMessage.empty() && updateMessage.back() == ';') {
            updateMessage.pop_back();
        }

        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::UPDATE_PARTIALS_POSITIONS_FROM_SERVER;
        responseMessage.id = 0;
        responseMessage.params = updateMessage;

        _message_compressor.serialize(responseMessage, response);
        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    std::string Room::sendExistingEntities()
    {
        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(_ecs._components_arrays[typeid(ecs::Position)]);
        auto &sprite = std::any_cast<ecs::SparseArray<SpriteId> &>(_ecs._components_arrays[typeid(SpriteId)]);

        std::string updateMessage = "";

        for (size_t i = 0; i < positions.size(); ++i) {
            if (positions[i].has_value() && sprite[i].has_value()) {
                int spriteId = sprite[i].value()._sprite;
                if (spriteId == MY_PLAYER_SHIP)
                    spriteId = OTHER_PLAYER_SHIP;
                updateMessage += std::to_string(positions[i].value()._pos_x) +
                "," + std::to_string(positions[i].value()._pos_y) +
                "," + std::to_string(i) +
                "," + std::to_string(spriteId) + ";";
            }
        }

        return updateMessage;
    }

    void Room::send_client_new_monster(size_t index_ecs_server, float x, float y, int type)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::CREATE_MONSTER;
        responseMessage.id = index_ecs_server;
        responseMessage.params = "x=" + std::to_string(x) + ";y=" + std::to_string(y) + ";type=" + std::to_string(type);

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_remove_ath()
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::REMOVE_ATH;
        responseMessage.id = 0;

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_roll_back()
    {
        std::string updateMessage = "";

        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(_ecs._components_arrays[typeid(ecs::Position)]);

        for (size_t i = 0; i < positions.size(); ++i) {
            if (positions[i].has_value()) {
                updateMessage += std::to_string(i) +
                                "," + std::to_string(static_cast<int>(round(positions[i].value()._pos_x))) +
                                "," + std::to_string(static_cast<int>(round(positions[i].value()._pos_y))) + ";";
            }
        }

        if (!updateMessage.empty() && updateMessage.back() == ';') {
            updateMessage.pop_back();
        }

        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::UPDATE_POSITIONS_FROM_SERVER;
        responseMessage.id = 0;
        responseMessage.params = updateMessage;

        _message_compressor.serialize(responseMessage, response);
        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_change_player_velocity(bool up)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        if (up) {
            responseMessage.action = RTYPE_ACTIONS::UP_VELOCITY;
        } else {
            responseMessage.action = RTYPE_ACTIONS::DOWN_VELOCITY;
        }
        responseMessage.id = 0;

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_player_shield(size_t index, bool put)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        if (put) {
            responseMessage.action = RTYPE_ACTIONS::PUT_SHIELD;
        } else {
            responseMessage.action = RTYPE_ACTIONS::REMOVE_SHIELD;
        }
        responseMessage.id = 0;
        responseMessage.params = std::to_string(index);

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_player_lifes(std::list<std::pair<size_t, int>> lifes)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.id = 0;
        responseMessage.action = RTYPE_ACTIONS::UPDATE_LIFE;

        for (auto life : lifes) {
            responseMessage.params += std::to_string(life.first) + "," + std::to_string(life.second) + ";";
        }

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }
}