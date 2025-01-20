
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

    #include "Includes.hpp"
    #include "Enums.hpp"

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
                        case SPRITES::GAME_BACKGROUND:
                            return std::make_tuple<float, float, float>(1.0f, 1.0, 0.0f);
                        case SPRITES::MY_PLAYER_SHIP:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::SIMPLE_MONSTER:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.2f);
                        case SPRITES::ADVANCED_MONSTER:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.2f);
                        case SPRITES::OTHER_PLAYER_SHIP:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::PLAYER_SIMPLE_MISSILE:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.10f);
                        case SPRITES::MONSTER_MULTIPLE_MISSILE:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.10f);
                        case SPRITES::MONSTER_SIMPLE_MISSILE:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.10f);
                        case SPRITES::FIRE_BALL:
                            return std::make_tuple<float, float, float>(5.0f, 5.0f, 0.50f);
                        case SPRITES::LEVEL1:
                            return std::make_tuple<float, float, float>(0.25f, 0.25f, 0.10f);
                        case SPRITES::LEVEL2:
                            return std::make_tuple<float, float, float>(0.25f, 0.25f, 0.10f);
                        case SPRITES::SIMPLE_BOSS:
                            return std::make_tuple<float, float, float>(5.0f, 5.0f, 0.5);
                        case SPRITES::LEVEL_BOSS:
                            return std::make_tuple<float, float, float>(0.25f, 0.25f, 0.10f);
                        case SPRITES::LEVEL_LOCK:
                            return std::make_tuple<float, float, float>(0.15f, 0.15, 0.10f);
                        case SPRITES::LOOSER_SCREEN:
                            return std::make_tuple<float, float, float>(0.5f, 0.5f, 0.35);
                        case SPRITES::WIN_SCREEN:
                            return std::make_tuple<float, float, float>(0.5f, 0.5f, 0.35);
                        case SPRITES::SUPER_MONSTER:
                            return std::make_tuple<float, float, float>(4.0f, 4.0f, 0.35);
                        case SPRITES::MEGA_MONSTER:
                            return std::make_tuple<float, float, float>(4.0f, 4.0f, 0.35);
                        case SPRITES::BABY_PROJECTILE:
                            return std::make_tuple<float, float, float>(2.5f, 2.5f, 0.35);
                        case SPRITES::ASTEROIDE:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.1);
                        case SPRITES::PLAYER_CHARGED_SHOOT:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4);
                        case SPRITES::CHARGED_ANIMATION:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.1);
                        case SPRITES::BOSS_PROJECTILE:
                            return std::make_tuple<float, float, float>(5.0f, 5.0f, 0.1);
                        case SPRITES::WEAPON_DROP:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.1);
                        case SPRITES::LIFE_DROP:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.1);
                        case SPRITES::SPEED_DROP:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.1);
                        case SPRITES::SHIELD_DROP:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.1);
                        case SPRITES::MY_PLAYER_SHIP_SHIELD:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::OTHER_PLAYER_SHIP_SHIELD:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::LIFE_RECTANGLE:
                            return std::make_tuple<float, float, float>(1.5f, 0.8f, 0.4f);
                        case SPRITES::LIFE_RED:
                            return std::make_tuple<float, float, float>(1.12f, 0.8f, 0.4f);
                        case SPRITES::LIFE_HEART:
                            return std::make_tuple<float, float, float>(1.0f, 1.0f, 0.4f);
                        case SPRITES::MY_PLAYER_SHIP_WEAPON:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::OTHER_PLAYER_SHIP_WEAPON:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4f);
                        case SPRITES::PLAYER_RED_MISSILE:
                            return std::make_tuple<float, float, float>(2.0f, 2.0f, 0.10f);
                        case SPRITES::PLAYER_RED_CHARGED_SHOOT:
                            return std::make_tuple<float, float, float>(3.0f, 3.0f, 0.4);
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
                    switch (id)
                    {
                        case SPRITES::MENU_BACKGROUND:
                            return {loadTexture("assets/backgrounds/background.png")};
                        case SPRITES::GAME_BACKGROUND:
                            return {loadTexture("assets/backgrounds/background_loop.png")};
                        case SPRITES::PLAYER_CHARGED_SHOOT:
                            return loadTextures("projectiles/charged_shoot", 0, 1);
                        case SPRITES::CHARGED_ANIMATION:
                            return loadTextures("projectiles/charged_animation", 0, 4);
                        case SPRITES::MY_PLAYER_SHIP:
                            return loadTextures("player_ship/player_blue_ship", 0, 4);
                        case SPRITES::SIMPLE_MONSTER:
                            return loadTextures("monsters/simple_monster", 0, 2);
                        case SPRITES::OTHER_PLAYER_SHIP:
                            return loadTextures("player_ship/player_red_ship", 0, 4);
                        case SPRITES::PLAYER_SIMPLE_MISSILE:
                            return loadTextures("projectiles/simple_player_missile", 0, 1);
                        case SPRITES::MONSTER_SIMPLE_MISSILE:
                            return loadTextures("projectiles/simple_monster_missile", 0, 7);
                        case SPRITES::MONSTER_MULTIPLE_MISSILE:
                            return loadTextures("projectiles/advanced_monster_missile", 0, 2);
                        case SPRITES::LEVEL1:
                            return {loadTexture("assets/levels/level1.png")};
                        case SPRITES::LEVEL2:
                            return {loadTexture("assets/levels/level2.png")};
                        case SPRITES::LEVEL_BOSS:
                            return {loadTexture("assets/levels/final_level.png")};
                        case SPRITES::LEVEL_LOCK:
                            return {loadTexture("assets/levels/level_lock.png")};
                        case SPRITES::BOSS_PROJECTILE:
                            return {loadTexture("assets/projectiles/boss_projectile.png")};
                        case SPRITES::LOOSER_SCREEN:
                            return loadTextures("winner_looser/looser_screen", 0, 7);
                        case SPRITES::WIN_SCREEN:
                            return loadTextures("winner_looser/win_screen", 0, 9);
                        case SPRITES::ADVANCED_MONSTER:
                            return loadTextures("monsters/monster_2", 0, 10);
                        case SPRITES::SUPER_MONSTER:
                            return loadTextures("monsters/advanced_monster", 0, 9);
                        case SPRITES::SIMPLE_BOSS:
                            return loadTextures("monsters/simple_boss", 0, 3);
                        case SPRITES::MEGA_MONSTER:
                            return loadTextures("monsters/monster_3", 0, 4);
                        case SPRITES::FIRE_BALL:
                            return loadTextures("projectiles/fire_ball", 0, 1);
                        case SPRITES::BABY_PROJECTILE:
                            return loadTextures("projectiles/baby_projectile", 0, 1);
                        case SPRITES::ASTEROIDE:
                            return loadTextures("projectiles/asteroide", 0, 11);
                        case SPRITES::WEAPON_DROP:
                            return {loadTexture("assets/bonuses/bonus_weapon.png")};
                        case SPRITES::LIFE_DROP:
                            return {loadTexture("assets/bonuses/bonus_life.png")};
                        case SPRITES::SPEED_DROP:
                            return {loadTexture("assets/bonuses/bonus_eclaire.png")};
                        case SPRITES::SHIELD_DROP:
                            return {loadTexture("assets/bonuses/bonus_shield.png")};
                        case SPRITES::MY_PLAYER_SHIP_SHIELD:
                            return loadTextures("player_ship/player_blue_ship_shield", 0, 4);
                        case SPRITES::OTHER_PLAYER_SHIP_SHIELD:
                            return loadTextures("player_ship/player_red_ship_shield", 0, 4);
                        case SPRITES::LIFE_RED:
                            return {loadTexture("assets/ath/red_life_rectangle.png")};
                        case SPRITES::LIFE_RECTANGLE:
                            return {loadTexture("assets/ath/life_rectangle.png")};
                        case SPRITES::LIFE_HEART:
                            return {loadTexture("assets/ath/life.png")};
                        case SPRITES::MY_PLAYER_SHIP_WEAPON:
                            return loadTextures("player_ship/rtype_vaisseau_weapon/vaisseau_weapon", 0, 4);
                        case SPRITES::OTHER_PLAYER_SHIP_WEAPON:
                            return loadTextures("player_ship/rtype_vaisseau_weapon/vaisseau_weapon_red", 0, 4);
                        case SPRITES::PLAYER_RED_MISSILE:
                            return loadTextures("projectiles/red_player_missile", 0, 1);
                        case SPRITES::PLAYER_RED_CHARGED_SHOOT:
                            return loadTextures("projectiles/charged_red_shoot", 0, 1);
                        default:
                            throw std::invalid_argument("Invalid sprite ID  in sprite: " + id);
                    }
                }

            private:
                static std::vector<std::shared_ptr<sf::Texture>> loadTextures(const std::string& category, int startFrame, int endFrame) {
                    std::vector<std::shared_ptr<sf::Texture>> textures;

                    for (int frame = startFrame; frame <= endFrame; ++frame) {
                        std::string filepath = generateFilePath(category, frame);
                        textures.push_back(loadTexture(filepath));
                    }

                    return textures;
                }

                static std::string generateFilePath(const std::string& category, int frame) {
                    return "assets/" + category + "_frame" + std::to_string(frame) + ".png";
                }

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
