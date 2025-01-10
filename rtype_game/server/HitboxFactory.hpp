/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitboxFactory
*/

/**
 * @file HitboxFactory.hpp
 * @brief Provides a factory for creating hitboxes for different sprites.
 */

#ifndef HitboxFactory_HPP_
#define HitboxFactory_HPP_

#include "../client/SpriteFactory.hpp"
#include "../shared/Enums.hpp"
#include "../shared/Includes.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
namespace rtype
{
    /**
     * @class HitboxFactory
     * @brief Factory class for generating hitboxes for entities based on sprite IDs.
     */
    class HitboxFactory
    {
    public:
        /**
         * @brief Creates a hitbox for a given sprite ID.
         * @param id The sprite ID.
         * @return A pair representing the width and height of the hitbox.
         * @throws std::invalid_argument If the sprite ID is invalid.
         */
        static std::pair<int, int> createHitbox(SPRITES id)
        {
            switch (id) {
            case SPRITES::MY_PLAYER_SHIP: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::MY_PLAYER_SHIP);
            }
            case SPRITES::SIMPLE_MONSTER: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::SIMPLE_MONSTER);
            }
            case SPRITES::ADVANCED_MONSTER: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::ADVANCED_MONSTER);
            }
            case SPRITES::OTHER_PLAYER_SHIP: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::OTHER_PLAYER_SHIP);
            }
            case SPRITES::PLAYER_SIMPLE_MISSILE: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::PLAYER_SIMPLE_MISSILE);
            }
            case SPRITES::MONSTER_SIMPLE_MISSILE: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::MONSTER_SIMPLE_MISSILE);
            }
            case SPRITES::MONSTER_MULTIPLE_MISSILE: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::MONSTER_MULTIPLE_MISSILE);
            }
            case SPRITES::FIRE_BALL: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::MONSTER_MULTIPLE_MISSILE);
            }
            case SPRITES::SUPER_MONSTER: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::SUPER_MONSTER);
            }
            case SPRITES::MEGA_MONSTER: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::SUPER_MONSTER);
            }
            case SPRITES::BABY_PROJECTILE: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::BABY_PROJECTILE);
            }
            case SPRITES::ASTEROIDE: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::ASTEROIDE);
            }
            default: {
                throw std::invalid_argument("Invalid sprite ID in hit box.");
            }
            }
        }

    private:
    };

}

#endif /* !HitboxFactory_HPP_ */
