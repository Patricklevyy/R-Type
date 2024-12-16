/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteFactory
*/

#ifndef SPRITEFACTORY_HPP_
    #define SPRITEFACTORY_HPP_

    #include "../shared/Includes.hpp"
    #include "../shared/Enums.hpp"

    namespace rtype
    {
        class SpriteFactory
            {
            public:
                static std::shared_ptr<sf::Sprite> createSprite(SPRITES id)
                {
                    std::string texturePath;
                    sf::Vector2f scale(1.0f, 1.0f);
                    switch (id)
                    {
                    case SPRITES::BACKGROUND:
                        texturePath = "assets/space-background.jpg";
                        scale = sf::Vector2f(1.0f, 1.0f);
                        break;
                    case SPRITES::SHIP:
                        texturePath = "assets/enemy-spaceship.png";
                        scale = sf::Vector2f(0.07f, 0.07f);
                        break;
                    // case SPRITES::MONSTER:
                    //     texturePath = "assets/red_ship.png"; sprite a definir
                    //     break;
                    case SPRITES::MISSILE:
                        texturePath = "assets/bullet.png";
                        scale = sf::Vector2f(0.03f, 0.03f);
                        break;
                    default:
                        throw std::invalid_argument("Invalid sprite ID");
                    }

                    auto texture = loadTexture(texturePath);

                    auto sprite = std::make_shared<sf::Sprite>();
                    sprite->setTexture(*texture);
                    sprite->setScale(scale);

                    return sprite;
                }

            private:
                static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> &getTextureCache()
                {
                    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textureCache;
                    return textureCache;
                }

                static std::shared_ptr<sf::Texture> loadTexture(const std::string &path)
                {
                    auto &textureCache = getTextureCache();

                    auto it = textureCache.find(path);
                    if (it != textureCache.end())
                    {
                        return it->second;
                    }

                    auto texture = std::make_shared<sf::Texture>();
                    if (!texture->loadFromFile(path))
                    {
                        throw std::runtime_error("Failed to load texture: " + path);
                    }

                    textureCache[path] = texture;
                    return texture;
                }
        };

    }

#endif /* !SPRITEFACTORY_HPP_ */
