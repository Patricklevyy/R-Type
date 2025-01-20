/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Room_Systems
*/

#include "Room.hpp"

namespace poc_game
{
    void Room::start_game()
    {
        isPlaying = true;
    }

    void Room::player_jump()
    {
        _direction_system.updatePlayerDirection(_ecs._components_arrays, ecs::direction::UP);
        _velocity_system.updatePlayerVelocity(_ecs._components_arrays, 3000);
    }

    void Room::restart_game()
    {
        isPlaying = true;
        send_client_create_player();
    }
}