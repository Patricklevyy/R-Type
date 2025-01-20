/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PlayerSystem
*/

/**
 * @file PlayerSystem.hpp
 * @brief Header file for the PlayerSystem class.
 *
 * This file contains the declaration of the PlayerSystem class, responsible for managing
 * the player entity's behaviors such as sprite change, life management, and other related features.
 */

#ifndef PLAYERSYSTEM_HPP_
    #define PLAYERSYSTEM_HPP_

    #include "../../../ecs/components/Playable.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../components/Displayable.hpp"
    #include "../components/Life.hpp"
    #include "../../shared/components/Health.hpp"


    namespace rtype
    {

        /**
         * @class PlayerSystem
         * @brief A system that manages player-specific functionalities such as health, sprite changes, etc.
         *
         * The PlayerSystem class provides various functions to manipulate a player entity's sprite,
         * life, and health. It interfaces with the ECS components to retrieve and modify data related to
         * the player and updates the display accordingly.
         */
        class PlayerSystem {
            public:
                /**
                 * @brief Default constructor for the PlayerSystem class.
                 */
                PlayerSystem() {}
                /**
                 * @brief Destructor for the PlayerSystem class.
                 */
                ~PlayerSystem() {}

                 /**
                 * @brief Get the index of the player (only used by the client).
                 *
                 * This method searches the ECS components for a playable entity and returns the
                 * index of the player. If no player is found, it returns -1.
                 *
                 * @param components_array The array of components of entities in the ECS system.
                 * @return The index of the player, or -1 if no player is found.
                 * 
                 * @exception std::exception If there is an error accessing the playables component.
                 * @exception Unknown exception If an unknown error occurs.
                 */
                int getIndexPlayer(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    try {
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

                        for (std::size_t i = 0; i < playables.size(); ++i)
                        {
                            if (i < playables.size() && playables[i].has_value())
                                return i;
                        }
                        return -1;
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTIN] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                    return -1;
                }
                
                /**
                 * @brief Change the sprite of a player entity.
                 *
                 * This method changes the sprite of a player at the specified index by setting
                 * a new sprite. It checks the playables and displayables components before modifying
                 * the sprite.
                 *
                 * @param components_array The array of components of entities in the ECS system.
                 * @param index The index of the player.
                 * @param sprite The new sprite to set.
                 * @return True if the sprite was successfully changed, false otherwise.
                 * 
                 * @exception std::exception If there is an error accessing the components.
                 * @exception Unknown exception If an unknown error occurs.
                 */
                bool changePlayerSprite(std::unordered_map<std::type_index, std::any> &components_array, size_t index, SPRITES sprite)
                {
                    try {
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                        auto &displayables = std::any_cast<ecs::SparseArray<Displayable> &>(components_array[typeid(Displayable)]);

                        if (index < playables.size() && playables[index].has_value() && index < displayables.size() && displayables[index].has_value()) {
                            displayables[index].value().setSprite(sprite);
                            return true;
                        }
                        return false;
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTIN] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                    return false;
                }

                /**
                 * @brief Change the sprite of a teammate.
                 *
                 * This method changes the sprite of a teammate at the specified index. It accesses
                 * the displayable component and sets the sprite accordingly.
                 *
                 * @param components_array The array of components of entities in the ECS system.
                 * @param index The index of the teammate.
                 * @param sprite The new sprite to set.
                 * 
                 * @exception std::exception If there is an error accessing the components.
                 * @exception Unknown exception If an unknown error occurs.
                 */
                void changeTeamateSprite(std::unordered_map<std::type_index, std::any> &components_array, size_t index, SPRITES sprite)
                {
                    try {
                        auto &displayables = std::any_cast<ecs::SparseArray<Displayable> &>(components_array[typeid(Displayable)]);

                        if (index < displayables.size() && displayables[index].has_value()) {
                            displayables[index].value().setSprite(sprite);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTIN] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

                /**
                 * @brief Update the player's life (health points).
                 *
                 * This method updates the player's health. It modifies the player's health and
                 * ensures it does not exceed the maximum health. The updated health value is returned.
                 *
                 * @param components_array The array of components of entities in the ECS system.
                 * @param index The index of the player.
                 * @param health The new health value.
                 * @return A pair containing a boolean indicating success and the updated health value.
                 */
                std::pair<bool, int> updatePlayerLife(std::unordered_map<std::type_index, std::any> &components_array, size_t index, int health) {
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);

                    if (index < playables.size() && playables[index].has_value() && index < healths.size() && healths[index].has_value()) {
                        healths[index].value()._health = health;
                        if (healths[index].value()._health > healths[index].value()._max_heath) {
                            healths[index].value()._health = healths[index].value()._max_heath;
                        }
                        return std::make_pair(true, healths[index].value()._health);
                    }
                    return std::make_pair(false, 0);
                }

                /**
                 * @brief Update the display of the player's life.
                 *
                 * This method updates the display of the player's health as a bar or indicator.
                 * It scales the life sprite to represent the current health out of the maximum health.
                 *
                 * @param components_array The array of components of entities in the ECS system.
                 * @param index The index of the player.
                 * 
                 * @exception std::exception If there is an error accessing the components.
                 * @exception Unknown exception If an unknown error occurs.
                 */
                void updateLifeDisplay(std::unordered_map<std::type_index, std::any> &components_array, size_t index) {
                    auto &life = std::any_cast<ecs::SparseArray<Life> &>(components_array[typeid(Life)]);
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);
                    auto &displayable = std::any_cast<ecs::SparseArray<Displayable> &>(components_array[typeid(Displayable)]);

                    for (std::size_t i = 0; i < life.size(); ++i)
                    {
                        if (life[i].has_value() && i < displayable.size() && displayable[i].has_value() && index < healths.size() && healths[index].has_value()) {
                            std::tuple<float, float, float> scale = SpriteFactory::getSpriteScaleAndSpeed(SPRITES::LIFE_RED);

                            float new_size = (std::get<0>(scale) / healths[index].value()._max_heath) * healths[index].value()._health;

                            displayable[i].value().setSpriteScale(new_size, std::get<1>(scale));
                        }
                    }
                }

            protected:
            private:
        };
    }

#endif /* !PLAYERSYSTEM_HPP_ */
