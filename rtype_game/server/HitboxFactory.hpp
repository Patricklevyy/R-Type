/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitboxFactory
*/

#ifndef HitboxFactory_HPP_
#define HitboxFactory_HPP_

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
    class HitboxFactory
    {
    public:
        static std::pair<int, int> getHitboxSize(SPRITES id)
        {
            std::string texturePath;
            sf::Vector2f scale(1.0f, 1.0f);

            switch (id) {
            case SPRITES::MENU_BACKGROUND:
                texturePath = "assets/background.png";
                scale = sf::Vector2f(1.0f, 1.0f);
                break;
            case SPRITES::GAME_BACKGROUND:
                texturePath = "assets/background_space_dynamic.jpg";
                scale = sf::Vector2f(1.0f, 1.0f);
                break;
            case SPRITES::MY_PLAYER_SHIP:
                texturePath = "assets/red_ship.png";
                break;
            case SPRITES::MONSTER:
                texturePath = "assets/enemy-spaceship.png";
                scale = sf::Vector2f(-0.04f, 0.04f);
                break;
            case SPRITES::OTHER_PLAYER_SHIP:
                texturePath = "assets/blue_ship.png";
                break;
            case SPRITES::PLAYER_SIMPLE_MISSILE:
                texturePath = "assets/bullet.png";
                scale = sf::Vector2f(0.03f, 0.03f);
                break;
            case SPRITES::MONSTER_SIMPLE_MISSILE:
                texturePath = "assets/monster_missile.png";
                scale = sf::Vector2f(1.0f, 1.0f);
                break;
            default:
                throw std::invalid_argument("Invalid sprite ID.");
            }

            sf::Texture texture;
            if (!texture.loadFromFile(texturePath)) {
                throw std::runtime_error("Unable to load texture: " + texturePath);
            }

            sf::Vector2u originalSize = texture.getSize();

            int hitboxWidth = static_cast<int>(originalSize.x * std::abs(scale.x));
            int hitboxHeight = static_cast<int>(originalSize.y * std::abs(scale.y));

            return {hitboxWidth, hitboxHeight};
        }

        static std::pair<int, int> createHitbox(SPRITES id)
        {
            switch (id) {
            case SPRITES::MY_PLAYER_SHIP: {
                std::cout << "MY_PLAYER_SHIP hitbox" << getHitboxSize(SPRITES::MY_PLAYER_SHIP).first << "-" << getHitboxSize(SPRITES::MY_PLAYER_SHIP).second
                          << std::endl;
                return getHitboxSize(SPRITES::MY_PLAYER_SHIP);
            }
            case SPRITES::MONSTER: {
                std::cout << "MONSTER hitbox" << getHitboxSize(SPRITES::MONSTER).first << "-" << getHitboxSize(SPRITES::MONSTER).second
                          << std::endl;
                return getHitboxSize(SPRITES::MONSTER);
            }
            case SPRITES::OTHER_PLAYER_SHIP: {
                std::cout << "OTHER_PLAYER_SHIP hitbox" << getHitboxSize(SPRITES::OTHER_PLAYER_SHIP).first << "-" << getHitboxSize(SPRITES::OTHER_PLAYER_SHIP).second
                          << std::endl;
                return getHitboxSize(SPRITES::OTHER_PLAYER_SHIP);
            }
            case SPRITES::PLAYER_SIMPLE_MISSILE: {
                std::cout << "PLAYER_SIMPLE_MISSILE hitbox" << getHitboxSize(SPRITES::PLAYER_SIMPLE_MISSILE).first << "-" << getHitboxSize(SPRITES::PLAYER_SIMPLE_MISSILE).second
                          << std::endl;
                return getHitboxSize(SPRITES::PLAYER_SIMPLE_MISSILE);
            }
            case SPRITES::MONSTER_SIMPLE_MISSILE: {
                std::cout << "MONSTER_SIMPLE_MISSILE hitbox" << getHitboxSize(SPRITES::MONSTER_SIMPLE_MISSILE).first << "-" << getHitboxSize(SPRITES::MONSTER_SIMPLE_MISSILE).second
                          << std::endl;
                return getHitboxSize(SPRITES::MONSTER_SIMPLE_MISSILE);
            }
            default: {
                throw std::invalid_argument("Invalid sprite ID.");
            }
            }
        }

    private:
    };

}

#endif /* !HitboxFactory_HPP_ */
