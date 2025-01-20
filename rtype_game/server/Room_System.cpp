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

        size_t player_index = bonuses.first;
        for (auto bonus : bonuses.second) {
            switch (bonus)
            {
            case BONUS::SHIELD:
                _bonus_system.updatePlayerTempShield(_ecs._components_arrays, player_index, SpriteFactory::getMaxTextureSizeForSprite(SPRITES::MY_PLAYER_SHIP), false);
                send_client_player_shield(player_index, false);
                break;
            case BONUS::VELOCITY:
                _bonus_system.changePlayerVelocity(_ecs._components_arrays, player_index, -_gameplay_factory->getVelocityBoostBonus());
                send_client_change_player_velocity(player_index, false);
                break;
            case BONUS::WEAPON:
                _bonus_system.updatePlayerTempWeapon(_ecs._components_arrays, player_index, SpriteFactory::getMaxTextureSizeForSprite(SPRITES::MY_PLAYER_SHIP_WEAPON));
                send_client_player_weapon(player_index, false);
                break;
            default:
                break;
            }
        }
    }
}