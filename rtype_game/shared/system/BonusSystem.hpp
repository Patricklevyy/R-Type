/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BonusSystem
*/

#ifndef BONUSSYSTEM_HPP_
#define BONUSSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/components/Playable.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/Enums_ecs.hpp"
    #include "../../../ecs/Includes_ecs.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../server/components/Hitbox.hpp"
    #include "../../server/components/PowerUp.hpp"

    namespace rtype
    {
        /**
         * @class BonusSystem
         * @brief A class that handles the bonus of the game.
         *
         * The BonusSystem class is managing every Bonus when an entity is killed
         */
        class BonusSystem {
            public:
                /**
                 * @brief Constructor for the BonusSystem class.
                 */
                BonusSystem() {}

                /**
                 * @brief Destructor for the BonusSystem class.
                 */
                ~BonusSystem() {}

                /**
                 * @brief Add life to a player after the bonus Life is taken.
                 * @param components_array A reference to an unordered map containing components indexed by type.
                 *        It represents the collection of components associated with various entities.
                 * @param index The index of the player entity whose life is to be updated.
                 * @param life The amount of life to add to the player.
                 */
                void addPlayerLife(std::unordered_map<std::type_index, std::any> &components_array, size_t index, int life) {
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

                    if (index < playables.size() && playables[index].has_value() && index < healths.size() && healths[index].has_value()) {
                        healths[index].value()._health += life;
                        if (healths[index].value()._health > healths[index].value()._max_heath) {
                            healths[index].value()._health = healths[index].value()._max_heath;
                        }
                    }
                }

                /**
                 * @brief Add speed to a player after the bonus Speed is taken.
                 * @param components_array A reference to an unordered map containing components indexed by type.
                 *        It represents the collection of components associated with various entities.
                 * @param index The index of the player entity whose speed is to be updated.
                 * @param velocity The new speed of the player.
                 */
                void changePlayerVelocity(std::unordered_map<std::type_index, std::any> &components_array, size_t index, int velocity) {
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                    auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array[typeid(ecs::Velocity)]);

                    if (index < playables.size() && playables[index].has_value() && index < velocities.size() && velocities[index].has_value()) {
                        velocities[index].value().velocity += velocity;
                    }
                }

                /**
                 * @brief Modify the speed of entities.
                 * @param components_array A reference to an unordered map containing components indexed by type.
                 *        It represents the collection of components associated with various entities.
                 * @param index The index of the entity whose speed need to be updated.
                 * @param velocity The speed of the entities.
                 */
                void changeEntityVelocity(std::unordered_map<std::type_index, std::any> &components_array, size_t index, int velocity) {
                    auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array[typeid(ecs::Velocity)]);

                    if (index < velocities.size() && velocities[index].has_value()) {
                        velocities[index].value().velocity += velocity;
                    }
                }

               /**
                 * @brief Manage the bonus that has been taken to set the duration of this effect.
                 * @param components_array A reference to an unordered map containing components indexed by type.
                 *        It represents the collection of components associated with various entities.
                 * @param index The index of the entity whose speed need to be updated.
                 * @param bonus The bonus that has been taken.
                 * @param bonus_duration The speed of the entities.
                 */
                void powerUp(std::unordered_map<std::type_index, std::any> &components_array, size_t index, BONUS bonus, int bonus_duration) {
                    auto &powerups = std::any_cast<ecs::SparseArray<PowerUp> &>(components_array[typeid(PowerUp)]);

                    if (index < powerups.size() && powerups[index].has_value()) {
                        std::cout << "BONUS ACTIVER" << bonus_duration << std::endl;
                        powerups[index].value().activateBonus(bonus, bonus_duration);
                    }
                }

               /**
                 * @brief Manage the shield of the player.
                 * @param components_array A reference to an unordered map containing components indexed by type.
                 *        It represents the collection of components associated with various entities.
                 * @param index The index of the entity whose speed need to be updated.
                 * @param x_y The position of the player.
                 * @param invincible Set invincible parameter on the player.
                 */
                void updatePlayerTempShield(std::unordered_map<std::type_index, std::any> &components_array, size_t index, std::pair<int, int> x_y, bool invicible) {
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                    auto &hitbox = std::any_cast<ecs::SparseArray<Hitbox> &>(components_array[typeid(Hitbox)]);
                    auto &powerups = std::any_cast<ecs::SparseArray<PowerUp> &>(components_array[typeid(PowerUp)]);

                    if (index < playables.size() && playables[index].has_value() && index < hitbox.size() && hitbox[index].has_value() && index < powerups.size() && powerups[index].has_value()) {
                        hitbox[index].value()._invicible = invicible;
                        hitbox[index].value().setHitbox(x_y);
                    }
                }

                /**
                  * @brief Manage the weapon of the player.
                  * @param components_array A reference to an unordered map containing components indexed by type.
                  *        It represents the collection of components associated with various entities.
                  * @param index The index of the entity whose speed need to be updated.
                  * @param x_y The position of the player.
                  * @param invincible Set invincible parameter on the player.
                  */
                void updatePlayerTempWeapon(std::unordered_map<std::type_index, std::any> &components_array, size_t index, std::pair<int, int> x_y, bool invicible) {
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                    auto &hitbox = std::any_cast<ecs::SparseArray<Hitbox> &>(components_array[typeid(Hitbox)]);
                    auto &powerups = std::any_cast<ecs::SparseArray<PowerUp> &>(components_array[typeid(PowerUp)]);

                    if (index < playables.size() && playables[index].has_value() && index < hitbox.size() && hitbox[index].has_value() && index < powerups.size() && powerups[index].has_value()) {
                        hitbox[index].value()._invicible = invicible;
                        hitbox[index].value().setHitbox(x_y);
                    }
                }

               /**
                 * @brief Check the bonus to update the effect.
                 * @param components_array A reference to an unordered map containing components indexed by type.
                 *        It represents the collection of Bonuses.
                 */
                std::list<std::pair<size_t, std::list<BONUS>>> checkBonus(std::unordered_map<std::type_index, std::any> &components_array) {
                    auto &powerups = std::any_cast<ecs::SparseArray<PowerUp> &>(components_array[typeid(PowerUp)]);

                    std::list<std::pair<size_t, std::list<BONUS>>> bonuses;
                    std::list<BONUS> possible_bonus;
                    for (size_t i = 0; i < powerups.size(); ++i) {
                        if (powerups[i].has_value()) {
                            possible_bonus = powerups[i].value().updateBonuses();
                            if (!possible_bonus.empty()) {
                                bonuses.push_back(std::make_pair(i, possible_bonus));
                            }
                        }
                    }
                    return bonuses;
                }

            protected:
            private:
        };
    }

#endif /* !BONUSSYSTEM_HPP_ */
