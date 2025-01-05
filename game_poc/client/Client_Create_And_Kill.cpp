/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Create_And_Kill
*/

#include "Client.hpp"

namespace poc_game
{
    void Client::add_level_status_screen(bool win, ecs::udp::Message &message)
    {
        killEntity(_kill_system.killPipes(_ecs));
        size_t index = getNextIndex();

        _ecs.addComponents<ecs::Position>(index, ecs::Position(_window_width / 4, _window_height / 4));
        _ecs.addComponents<TempDisplay>(index, TempDisplay());
        _ecs.addComponents<Displayable>(index, Displayable(REPLAY_BUTTON));
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

                std::cout << " KILL enity " << id << " , " << index_ecs_client << std::endl;
                _kill_system.killEntity(_ecs, index_ecs_client);
            }
        }
    }

    void Client::createEntity(unsigned int server_id, float x, float y, SPRITES sprite_id)
    {
        size_t index = getNextIndex();
        std::cout << "JE CREATE : " << server_id << " , " << index << std::endl;
        ecs::Position position(x, y);
        Displayable displayable(sprite_id);
        Health health(60);

        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Displayable>(index, displayable);

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }
}