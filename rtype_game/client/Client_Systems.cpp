/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Systems
*/

#include "Client.hpp"

namespace rtype
{
    void Client::set_window_filter(FILTER_MODE filter)
    {
        _filter_system.setFilter(_ecs._components_arrays, filter);
    }

    void Client::change_player_direction(ecs::direction x, ecs::direction y)
    {
        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(x, y, _player_system.getIndexPlayer(_ecs._components_arrays));
        send_server_player_direction(x, y);
        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
    }
}