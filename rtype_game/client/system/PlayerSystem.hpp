/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PlayerSystem
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
         * @brief Handles player-related functionalities such as managing player index, sprite, life, and related visual updates.
         */
        class PlayerSystem {
            public:
                /**
                 * @brief Default constructor for the PlayerSystem class.
                 */
                PlayerSystem() {}

                /**
                 * @brief Default destructor for the PlayerSystem class.
                 */
                ~PlayerSystem() {}

                /**
                 * @brief Return the index of the player, used only by the client.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
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
                        return 0;
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTIN] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                    return 0;
                }

                /**
                 * @brief Changes the sprite of the player entity.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @param index The index of the player entity whose sprite is to be changed.
                 * @param sprite The new sprite to assign to the player.
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
                 * @brief Changes the sprite of a teammate entity.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @param index The index of the teammate entity whose sprite is to be changed.
                 * @param sprite The new sprite to assign to the teammate.
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
                     * @brief Updates the player's health.
                     * @param components_array A reference to a map containing ECS components indexed by their type.
                     * @param index The index of the player entity whose health is to be updated.
                     * @param health The new health value to set for the player.
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
                 * @brief Updates the visual representation of the player's health.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @param index The index of the player entity whose life bar is to be updated.
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
