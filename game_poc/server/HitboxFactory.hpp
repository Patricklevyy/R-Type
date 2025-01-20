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
namespace poc_game
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
            case SPRITES::PIPE_DOWN: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::PIPE_DOWN);
            }
            case SPRITES::PIPE_UP: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::PIPE_UP);
            }
            case SPRITES::PLAYER: {
                return SpriteFactory::getMaxTextureSizeForSprite(SPRITES::PLAYER);
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
