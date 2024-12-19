/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Background
*/

/**
 * @file Background.hpp
 * @brief Defines class for managing game background in the R-Type game.
 */

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

namespace rtype
{
    /**
     * @brief Represents the game background using an SFML sprite.
     */
    class Background
    {
    public:
        /**
         * @brief Constructs a background object with a texture and initial position.
         *
         * @param texturePath Path to the texture file.
         * @param x Initial x-coordinate of the background sprite.
         * @param y Initial y-coordinate of the background sprite.
         * @throws std::runtime_error If the texture fails to load.
         */
        Background(const std::string &texturePath, int x, int y)
        {
            try
            {
                texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile(texturePath))
                {
                    throw std::runtime_error("Failed to load texture from: " + texturePath);
                }
                std::cout << "[INFO] Texture loaded successfully from: " << texturePath
                          << " (Size: " << texture->getSize().x << "x" << texture->getSize().y << ")" << std::endl;

                sprite.setTexture(*texture);
                sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
                std::cout << "[INFO] Sprite initialized at position: (" << x << ", " << y << ")" << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << "[ERROR] " << e.what() << std::endl;
                throw;
            }
        }

        /**
         * @brief Gets the SFML sprite representing the background.
         *
         * @return Reference to the background sprite.
         */
        sf::Sprite &getSprite() { return sprite; }

    private:
        std::shared_ptr<sf::Texture> texture; /**< Shared pointer to the texture. */
        sf::Sprite sprite; /**< SFML sprite representing the background. */
    };
}

#endif /* BACKGROUND_HPP_ */
