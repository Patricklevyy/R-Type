
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

    namespace rtype
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
                        case SPRITES::MENU_BACKGROUND:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.0f);
                        case SPRITES::CREATE_ROOM_BTN:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.0f);
                        case SPRITES::CHANGE_KEY_BUTTON:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.0f);
                        case SPRITES::GAME_BACKGROUND:
                            return std::make_tuple<float, float, float>(1.0f, 1.0, 0.0f);
                        case SPRITES::MY_PLAYER_SHIP:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::SIMPLE_MONSTER:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.2f);
                        case SPRITES::ADVANCED_MONSTER:
                            return std::make_tuple<float, float, float>(-2.0f, 2.0f, 0.2f);
                        case SPRITES::OTHER_PLAYER_SHIP:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::PLAYER_SIMPLE_MISSILE:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.10f);
                        case SPRITES::MONSTER_MULTIPLE_MISSILE:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.10f);
                        case SPRITES::MONSTER_SIMPLE_MISSILE:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.10f);
                        case SPRITES::LEVEL1:
                            return std::make_tuple<float, float, float>(0.25f, 0.25f, 0.10f);
                        case SPRITES::LEVEL2:
                            return std::make_tuple<float, float, float>(0.25f, 0.25f, 0.10f);
                        case SPRITES::LEVEL_BOSS:
                            return std::make_tuple<float, float, float>(0.25f, 0.25f, 0.10f);
                        case SPRITES::LEVEL_LOCK:
                            return std::make_tuple<float, float, float>(0.15f, 0.15, 0.10f);
                        case SPRITES::LOOSER_SCREEN:
                            return std::make_tuple<float, float, float>(0.5f, 0.5f, 0.35);
                        case SPRITES::WIN_SCREEN:
                            return std::make_tuple<float, float, float>(0.5f, 0.5f, 0.35);
                        case SPRITES::EXIT_BUTTON:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.0f);

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
                        case SPRITES::MENU_BACKGROUND:
                            textures.push_back(loadTexture("assets/backgrounds/background.png"));
                            break;
                        case SPRITES::EXIT_BUTTON:
                            textures.push_back(loadTexture("assets/buttons/create_room_button.png")); // Ajoute une texture pour le bouton "Exit"
                            break;

                        case SPRITES::CHANGE_KEY_BUTTON:
                            textures.push_back(loadTexture("assets/buttons/create_room_button.png"));
                            break;

                        case SPRITES::CREATE_ROOM_BTN:
                            textures.push_back(loadTexture("assets/buttons/create_room_button.png"));
                            break;
                        case SPRITES::GAME_BACKGROUND:
                            textures.push_back(loadTexture("assets/backgrounds/background_loop.png"));
                            break;
                        case SPRITES::MY_PLAYER_SHIP:
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame1.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame2.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame3.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame4.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame5.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame4.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame3.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_blue_ship_frame2.png"));
                            break;
                        case SPRITES::SIMPLE_MONSTER:
                            textures.push_back(loadTexture("assets/monsters/simple_monster_frame1.png"));
                            textures.push_back(loadTexture("assets/monsters/simple_monster_frame2.png"));
                            textures.push_back(loadTexture("assets/monsters/simple_monster_frame3.png"));
                            break;
                        case SPRITES::OTHER_PLAYER_SHIP:
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame1.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame2.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame3.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame4.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame5.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame4.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame3.png"));
                            textures.push_back(loadTexture("assets/player_ship/player_red_ship_frame2.png"));
                            break;
                        case SPRITES::PLAYER_SIMPLE_MISSILE:
                            textures.push_back(loadTexture("assets/projectiles/simple_player_missile_frame1.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_player_missile_frame2.png"));
                            break;
                        case SPRITES::MONSTER_SIMPLE_MISSILE:
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame1.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame2.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame3.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame4.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame5.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame6.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame7.png"));
                            textures.push_back(loadTexture("assets/projectiles/simple_monster_missile_frame8.png"));
                            break;
                        case SPRITES::MONSTER_MULTIPLE_MISSILE:
                            textures.push_back(loadTexture("assets/projectiles/advanced_monster_missile_frame1.png"));
                            textures.push_back(loadTexture("assets/projectiles/advanced_monster_missile_frame2.png"));
                            textures.push_back(loadTexture("assets/projectiles/advanced_monster_missile_frame3.png"));
                            break;
                        case SPRITES::LEVEL1:
                            textures.push_back(loadTexture("assets/levels/level1.png"));
                            break;
                        case SPRITES::LEVEL2:
                            textures.push_back(loadTexture("assets/levels/level2.png"));
                            break;
                        case SPRITES::LEVEL_BOSS:
                            textures.push_back(loadTexture("assets/levels/final_level.png"));
                            break;
                        case SPRITES::LEVEL_LOCK:
                            textures.push_back(loadTexture("assets/levels/level_lock.png"));
                            break;
                        case SPRITES::LOOSER_SCREEN:
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame1.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame2.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame3.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame4.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame5.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame6.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame7.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame6.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame5.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame4.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame3.png"));
                            textures.push_back(loadTexture("assets/winner_looser/looser_screen_frame2.png"));
                            break;
                        case SPRITES::WIN_SCREEN:
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame1.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame2.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame3.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame4.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame5.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame6.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame7.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame8.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame9.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame8.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame7.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame6.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame5.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame4.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame3.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame2.png"));
                            textures.push_back(loadTexture("assets/winner_looser/win_screen_frame1.png"));
                            break;
                        case SPRITES::ADVANCED_MONSTER:
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame1.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame2.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame3.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame4.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame5.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame6.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame7.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame8.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame9.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame10.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame11.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame10.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame9.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame8.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame7.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame6.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame5.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame4.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame3.png"));
                            textures.push_back(loadTexture("assets/monsters/monster_2_frame2.png"));
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
