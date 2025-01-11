/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Create_And_Kill
*/

#include "Client.hpp"

namespace rtype
{
    void Client::add_level_status_screen(bool win, ecs::udp::Message &message)
    {
        size_t index = getNextIndex();

        SPRITES screen;
        if (win) {
            screen = SPRITES::WIN_SCREEN;
            _levels_wins[static_cast<LEVELS>(std::stoi(message.params) + 1)] = true;
        } else {
            screen = SPRITES::LOOSER_SCREEN;
        }
        _ecs.addComponents<ecs::Position>(index, ecs::Position(_window_width / 4, _window_height / 4));
        _ecs.addComponents<LevelStatus>(index, LevelStatus());
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

                _kill_system.killEntity(_ecs, index_ecs_client);
            }
        }
    }

    void Client::createEntity(unsigned int server_id, float x, float y, SPRITES sprite_id)
    {
        size_t index = getNextIndex();
        std::cout << "JE CREATE : " << index << std::endl;
        ecs::Position position(x, y);
        Displayable displayable(sprite_id);

        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Displayable>(index, displayable);

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::createPlayer(unsigned int server_id, float x, float y)
    {
        std::cout << "NEW PLAYER \n\n\n\n\n\n\n" << std::endl;
        size_t index = getNextIndex();

        ecs::Direction direction;
        ecs::Playable playable(_name);
        ecs::Position position(x, y);
        ecs::Velocity velocity(_gameplay_factory->getPlayerVelocity());
        Displayable displayable(SPRITES::MY_PLAYER_SHIP);

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Playable>(index, playable);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Displayable>(index, displayable);

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::createEntityProjectile(unsigned int server_id, float x, float y, int dir_x, int dir_y, int velocity, int spriteId)
    {
        size_t index = getNextIndex();

        _ecs.addComponents<ecs::Position>(index, ecs::Position(x, y));
        _ecs.addComponents<ecs::Direction>(index, ecs::Direction(static_cast<ecs::direction>(dir_x), static_cast<ecs::direction>(dir_y)));
        _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(velocity));
        _ecs.addComponents<Displayable>(index, Displayable(static_cast<SPRITES>(spriteId)));

        std::cout << "VELOCITY  " << velocity << std::endl;
        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::createProjectile(ecs::udp::Message &message)
    {
        float x = 0.0f, y = 0.0f;
        int dir_x, dir_y, velocity, type;

        std::vector<std::string> parts;
        std::stringstream ss(message.params);
        std::string part;

        while (std::getline(ss, part, ';')) {
            parts.push_back(part);
        }

        x = std::stof(parts[0].substr(parts[0].find('=') + 1));
        y = std::stof(parts[1].substr(parts[1].find('=') + 1));
        dir_x = std::stoi(parts[2].substr(parts[2].find('=') + 1));
        dir_y = std::stoi(parts[3].substr(parts[3].find('=') + 1));
        velocity = std::stoi(parts[4].substr(parts[4].find('=') + 1));
        type = std::stoi(parts[5].substr(parts[5].find('=') + 1));

        createEntityProjectile(message.id, x, y, dir_x, dir_y, velocity, type);
    }

    void Client::create_new_player_shoot()
    {
        send_server_new_shoot();
    }
}