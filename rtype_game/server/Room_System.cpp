/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Room_System
*/

#include "Room.hpp"

namespace rtype
{
    void Room::desactivateBonus(std::pair<size_t, std::list<BONUS>> bonuses) {

        std::cout << " DESTROY BONUS " << std::endl;
        size_t player_index = bonuses.first;
        for (auto bonus : bonuses.second) {
            switch (bonus)
            {
            case BONUS::SHIELD:
                _bonus_system.destroyPlayerTempShield(_ecs._components_arrays, player_index);
                send_client_player_shield(player_index, false);
                break;
            case BONUS::VELOCITY:
                _bonus_system.changePlayerVelocity(_ecs._components_arrays, player_index, -_gameplay_factory->getVelocityBoostBonus());
                send_client_change_player_velocity(false);
            default:
                break;
            }
        }
    }
}