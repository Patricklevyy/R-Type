/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Displayable
*/

/**
 * @file Displayable.hpp
 * @brief Defines classes to represent a displayable Component
 */

#ifndef DISPLAYABLE_HPP_
#define DISPLAYABLE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>
#include "../../shared/SpriteFactory.hpp"

namespace rtype {
    class Displayable {
    public:
        /**
         * @brief Constructs a displayable object with a given sprite ID.
         *
         * @param sprite_id Identifier for the sprite's textures and animation properties.
         * @throws std::runtime_error If no textures are available for the sprite ID.
         */
        Displayable(SPRITES sprite_id)
            : currentFrame(0), elapsedTime(0.0f)
        {
            textures = SpriteFactory::loadTexturesForSprite(sprite_id);
            std::tuple<float, float, float> scales_and_speed = SpriteFactory::getSpriteScaleAndSpeed(sprite_id);

            animationSpeed = std::get<2>(scales_and_speed);
            if (textures.empty()) {
                throw std::runtime_error("No textures available for sprite ID");
            }
            sprite = std::make_shared<sf::Sprite>();
            sprite->setTexture(*textures[currentFrame]);
            sprite->setScale(std::get<0>(scales_and_speed), std::get<1>(scales_and_speed));
        }

        /**
         * @brief Updates the animation frame based on elapsed time.
         *
         * @param deltaTime Time elapsed since the last update in seconds.
         */
        void update(float deltaTime) {
            elapsedTime += deltaTime;
            if (elapsedTime >= animationSpeed) {
                elapsedTime = 0.0f;
                currentFrame = (currentFrame + 1) % textures.size();
                sprite->setTexture(*textures[currentFrame]);
            }
        }

        /**
         * @brief Gets the current sprite being displayed.
         *
         * @return Shared pointer to the SFML sprite.
         */
        std::shared_ptr<sf::Sprite> getSprite()
        {
            return sprite;
        }

        /**
         * @brief Sets the position of the sprite.
         *
         * @param x The x-coordinate of the position.
         * @param y The y-coordinate of the position.
         */
        void setSpritePosition(float x, float y) {
            sprite->setPosition(x, y);
        }

        /**
         * @brief Updates the displayable object to use a new sprite ID.
         *
         * @param new_sprite_id The new sprite ID to load textures and animation properties.
         * @throws std::runtime_error If no textures are available for the new sprite ID.
         */
        void setSprite(SPRITES new_sprite_id) {
            sprite.reset();
            currentFrame = 0;
            textures = SpriteFactory::loadTexturesForSprite(new_sprite_id);
            std::tuple<float, float, float> scales_and_speed = SpriteFactory::getSpriteScaleAndSpeed(new_sprite_id);

            animationSpeed = std::get<2>(scales_and_speed);

            if (textures.empty()) {
                throw std::runtime_error("No textures available for sprite ID");
            }

            sprite = std::make_shared<sf::Sprite>();
            sprite->setTexture(*textures[currentFrame]);
            sprite->setScale(std::get<0>(scales_and_speed), std::get<1>(scales_and_speed));
        }

        sf::Vector2f getSpriteSize() const {
            if (sprite && sprite->getTexture()) {
                auto textureSize = sprite->getTexture()->getSize();
                auto scale = sprite->getScale();
                return sf::Vector2f(
                    textureSize.x * scale.x,
                    textureSize.y * scale.y
                );
            }
            return sf::Vector2f(0, 0);
        }

         void setSpriteScale(float scaleX, float scaleY) {
            if (sprite) {
                sprite->setScale(scaleX, scaleY);
            } else {
                throw std::runtime_error("Sprite is not initialized");
            }
        }

    private:
        std::shared_ptr<sf::Sprite> sprite;
        std::vector<std::shared_ptr<sf::Texture>> textures;
        size_t currentFrame;
        float animationSpeed;
        float elapsedTime;
    };

}

#endif /* DISPLAYABLE_HPP_ */
