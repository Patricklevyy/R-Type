
/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SpriteFactory
*/

/**
 * @file SpriteFactory.hpp
 * @brief Factory class for creating and handling sprites.
 *
 * The `SpriteFactory` class provides methods for retrieving sprite properties, loading
 * textures, and handling sprite scaling and speed based on the sprite type.
 */

#ifndef SPRITEFACTORY_HPP_
    #define SPRITEFACTORY_HPP_

    #include "../shared/Includes.hpp"
    #include "../shared/Enums.hpp"
    #include <cmath>

    namespace poc_game
    {
        class SpriteFactory
            {
            public:

                /**
                 * @brief Retrieves the scale and speed for a given sprite type.
                 * @param id The sprite identifier.
                 * @return A tuple containing the scale (x, y) and speed for the sprite.
                 */
                static std::tuple<float, float, float> getSpriteScaleAndSpeed(SPRITES id)
                {
                    switch (id)
                    {
                        case SPRITES::BACKGROUND:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.0f);
                        case SPRITES::PLAYER:
                            return std::make_tuple<float, float, float>(0.2f, 0.2f, 0.0f);
                        case SPRITES::PIPE_DOWN:
                            return std::make_tuple<float, float, float>(0.2f, 0.2f, 0.0f);
                        case SPRITES::PIPE_UP:
                            return std::make_tuple<float, float, float>(0.2f, -0.2f, 0.0f);
                        case SPRITES::PLAY_BUTTON:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.0f);
                        case SPRITES::REPLAY_BUTTON:
                            return std::make_tuple<float, float, float>(0.5f, 0.5f, 0.0f);
                        default:
                            throw std::invalid_argument("Invalid sprite ID in sprite and scale : " + id);
                    }
                }

                /**
                 * @brief Retrieves the maximum texture size for a given sprite type.
                 * @param id The sprite identifier.
                 * @return A pair containing the maximum width and height for the sprite.
                 */
                static std::pair<int, int> getMaxTextureSizeForSprite(SPRITES id)
                {
                    auto textures = loadTexturesForSprite(id);
                    auto scale = getSpriteScaleAndSpeed(id);
                    int maxWidth = 0;
                    int maxHeight = 0;

                    for (const auto &texture : textures) {
                        if (texture) {
                            sf::Vector2u size = texture->getSize();
                            maxWidth = std::max(maxWidth, static_cast<int>(size.x));
                            maxHeight = std::max(maxHeight, static_cast<int>(size.y));
                        }
                    }
                    return {(maxWidth * std::abs(std::get<0>(scale))), (maxHeight * std::abs(std::get<1>(scale)))};
                }

                /**
                 * @brief Loads the textures for a given sprite type.
                 * @param id The sprite identifier.
                 * @return A vector of shared pointers to sf::Texture objects for the sprite.
                 */
                static std::vector<std::shared_ptr<sf::Texture>> loadTexturesForSprite(SPRITES id)
                {
                    std::vector<std::shared_ptr<sf::Texture>> textures;
                    switch (id)
                    {
                        case SPRITES::BACKGROUND:
                            textures.push_back(loadTexture("game_poc/assets/background/flappy_bird_background.png"));
                            break;
                        case SPRITES::PLAYER:
                            textures.push_back(loadTexture("game_poc/assets/player/bird.png"));
                            break;
                        case SPRITES::PIPE_UP:
                            textures.push_back(loadTexture("game_poc/assets/pipe/pipe.png"));
                            break;
                        case SPRITES::PIPE_DOWN:
                            textures.push_back(loadTexture("game_poc/assets/pipe/pipe.png"));
                            break;
                        case SPRITES::PLAY_BUTTON:
                            textures.push_back(loadTexture("game_poc/assets/play_button.png"));
                            break;
                        case SPRITES::REPLAY_BUTTON:
                            textures.push_back(loadTexture("game_poc/assets/replay_button.png"));
                            break;
                        default:
                            throw std::invalid_argument("Invalid sprite ID  in sprite: " + id);
                    }

                    return textures;
                }

            private:
                 /**
                 * @brief Retrieves the texture cache for the sprite factory.
                 * @return A reference to the texture cache map.
                 */
                static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> &getTextureCache()
                {
                    static std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textureCache;
                    return textureCache;
                }

                /**
                 * @brief Loads a texture from a file.
                 * @param path The path to the texture file.
                 * @return A shared pointer to the loaded sf::Texture.
                 */
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
