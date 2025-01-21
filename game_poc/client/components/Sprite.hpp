/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

/**
 * @file Sprite.hpp
 * @brief Represents a drawable sprite with various transformations.
 */

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

namespace poc_game {
    /**
     * @class Sprite
     * @brief Class that handles all the sprites.
     */
    class Sprite {
    public:
        /**
         * @brief Default constructor for the sprite.
         */
        Sprite() = default;

        /**
         * @brief Constructs a sprite object with a texture, width, and height.
         *
         * @param texturePath Path to the texture file.
         * @param width Width to scale the sprite to.
         * @param height Height to scale the sprite to.
         * @throws std::runtime_error If the texture fails to load.
         */
        Sprite(const std::string& texturePath, float width, float height) {
            if (!texture->loadFromFile(texturePath)) {
                throw std::runtime_error("Failed to load texture: " + texturePath);
            }
            sprite.setTexture(*texture);
            sprite.setScale(width / texture->getSize().x, height / texture->getSize().y);
        }

        /**
         * @brief Sets the position of the sprite.
         *
         * @param x The x-coordinate of the new position.
         * @param y The y-coordinate of the new position.
         */
        void setPosition(float x, float y)
        {
            sprite.setPosition(x, y);
        }

        /**
         * @brief Gets the position of the sprite.
         *
         * @return The current position of the sprite as a 2D vector.
         */
        sf::Vector2f getPosition() const
        {
            return sprite.getPosition();
        }

        /**
         * @brief Draws the sprite to the specified render window.
         *
         * @param window The SFML render window to draw the sprite on.
         */
        void draw(sf::RenderWindow& window) const
        {
            window.draw(sprite);
        }

        /**
         * @brief Sets the rotation of the sprite.
         *
         * @param angle The rotation angle in degrees.
         */
        void setRotation(float angle)
        {
            sprite.setRotation(angle);
        }

        /**
         * @brief Gets the current rotation angle of the sprite.
         *
         * @return The rotation angle in degrees.
         */
        float getRotation() const
        {
            return sprite.getRotation();
        }

    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
    };
}

#endif /* SPRITE_HPP_ */
