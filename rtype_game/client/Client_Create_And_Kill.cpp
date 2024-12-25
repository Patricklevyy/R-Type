/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Create_And_Kill
*/

#include "Client.hpp"

namespace rtype
{
    void Client::add_level_status_screen(bool win)
    {
        size_t index = getNextIndex();

        SPRITES screen;
        if (win) {
            screen = SPRITES::WIN_SCREEN;
        } else {
            screen = SPRITES::LOOSER_SCREEN;
        }
        _ecs.addComponents<ecs::Position>(index, ecs::Position(_window_width / 4, _window_height / 4));
        _ecs.addComponents<TempDisplay>(index, TempDisplay());
        _ecs.addComponents<Displayable>(index, Displayable(screen));
    }

    void Client::killEntity(std::list<size_t> entities_id)
    {
        size_t index_ecs_client;

        for (const auto &id : entities_id) {
            auto it = ecs_server_to_client.find(id);
            if (it != ecs_server_to_client.end()) {
                index_ecs_client = it->second;
                ecs_server_to_client.erase(it);

                it = ecs_client_to_server.find(index_ecs_client);
                ecs_client_to_server.erase(it);

                _ecs.killEntityFromRegistry<ecs::Position>(index_ecs_client);
                _ecs.killEntityFromRegistry<Health>(index_ecs_client);
                _ecs.killEntityFromRegistry<Sprite>(index_ecs_client);
                _ecs.killEntityFromRegistry<Displayable>(index_ecs_client);
                _ecs.killEntityFromRegistry<ecs::Playable>(index_ecs_client);
                _ecs.addDeadEntity(index_ecs_client);
            }
        }
    }

    void Client::createEntity(unsigned int server_id, float x, float y, SPRITES sprite_id)
    {
        size_t index = getNextIndex();
        std::cout << "JE CREATE : " << index << std::endl;
        ecs::Position position(x, y);
        Displayable displayable(sprite_id);
        Health health(60);

        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Displayable>(index, displayable);

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::createMonster(ecs::udp::Message &message)
    {
        // size_t index = getNextIndex();
        // std::unordered_map<std::string, std::string> res = MessageChecker::parseResponse(message.params);
        // if (res.find("x") == res.end() || res.find("y") == res.end()) {
        //     std::cerr << "Error: Missing x or y in message parameters" << std::endl;
        //     return;
        // }
        // int x = std::stof(res["x"]);
        // int y = std::stof(res["y"]);
        // ecs::Position position(x, y);
        // Displayable displayable(SPRITES::SIMPLE_MONSTER);
        // Health health(60);

        // _ecs.addComponents<ecs::Position>(index, position);
        // _ecs.addComponents<Health>(index, health);
        // _ecs.addComponents<Displayable>(index, displayable);

        // std::cout << "Monstre créé à l'index : " << index << " (" << x << ", " << y << ")" << std::endl;
    }

    void Client::createPlayer(unsigned int server_id, float x, float y)
    {
        std::cout << "NEW PLAYER \n\n\n\n\n\n\n" << std::endl;
        size_t index = getNextIndex();

        ecs::Direction direction;
        ecs::Playable playable(_name);
        ecs::Position position(x, y);
        ecs::Velocity velocity(200);
        Displayable displayable(SPRITES::MY_PLAYER_SHIP);
        Health health(100);

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Playable>(index, playable);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Displayable>(index, displayable);
        _ecs.addComponents<Health>(index, health);

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::createProjectile(ecs::udp::Message &message)
    {
        float x = 0.0f, y = 0.0f;
        int type = 0;

        std::vector<std::string> parts;
        std::stringstream ss(message.params);
        std::string part;

        while (std::getline(ss, part, ';')) {
            parts.push_back(part);
        }

        x = std::stof(parts[0].substr(parts[0].find('=') + 1));
        y = std::stof(parts[1].substr(parts[1].find('=') + 1));
        type = std::stoi(parts[2].substr(parts[2].find('=') + 1));

        SPRITES spriteType = static_cast<SPRITES>(type);

        createEntity(message.id, x, y, spriteType);
    }
}