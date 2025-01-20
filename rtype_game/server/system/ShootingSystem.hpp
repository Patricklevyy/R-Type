/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ShootingSystem
*/

/**
 * @file ShootingSystem.hpp
 * @brief Handles shooting mechanics for monster entities.
 */

#ifndef SHOOTINGSYSTEM_HPP_
    #define SHOOTINGSYSTEM_HPP_

    #include "../components/Monster.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include <list>
    #include "../../shared/Enums.hpp"

    namespace rtype
    {
        /**
         * @class ShootingSystem
         * @brief Manages shooting behavior for monsters.
         */
        class ShootingSystem
        {
        public:

            /**
             * @brief Determines which monsters should shoot and returns shooting details.
             * @param components_array A map containing all component arrays.
             * @param randomizer Random number generator for determining shooting intervals.
             * @return A list of shooting entities and their details.
             */
            std::list<std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>> monster_shooting(std::unordered_map<std::type_index, std::any> &components_array, RandomNumber randomizer, int window_width, int window_height)
            {
                auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(components_array[typeid(Monster)]);
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);
                auto &healthes = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);

                std::list<std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>> shooting_entities;
                std::pair<std::pair<float, float>, std::pair<float, float>> nested_pair;
                for (size_t i = 0; i < monsters.size(); ++i) {
                    if (monsters[i].has_value() && positions[i].has_value() && i < healthes.size() && healthes[i].has_value()) {
                        switch (monsters[i].value()._monster)
                        {
                        case SPRITES::SIMPLE_MONSTER:
                            if (monsters[i].value().getElapsedTime() > monsters[i].value()._intValue) {
                                nested_pair = {
                                    {positions[i].value()._pos_x, positions[i].value()._pos_y},
                                    {ecs::direction::LEFT, ecs::direction::NO_DIRECTION}
                                };

                                shooting_entities.push_back(std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                                    i,
                                    nested_pair,
                                    SPRITES::MONSTER_SIMPLE_MISSILE
                                ));

                                monsters[i].value()._intValue = randomizer.generateRandomNumbers(2, 5);
                                monsters[i].value().resetTimer();
                            }
                            break;
                        case SPRITES::ADVANCED_MONSTER:
                            if (monsters[i].value().getElapsedTime() > monsters[i].value()._intValue) {
                                std::pair<std::pair<float, float>, std::pair<float, float>> nested_pair = {
                                    {positions[i].value()._pos_x, positions[i].value()._pos_y + 40},
                                    {ecs::direction::LEFT, ecs::direction::NO_DIRECTION}
                                };
                                shooting_entities.push_back(std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                                    i,
                                    nested_pair,
                                    SPRITES::MONSTER_MULTIPLE_MISSILE
                                ));
                                nested_pair.first = std::make_pair(positions[i].value()._pos_x, positions[i].value()._pos_y - 40);

                                shooting_entities.push_back(std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                                    i,
                                    nested_pair,
                                    SPRITES::MONSTER_MULTIPLE_MISSILE
                                ));
                                monsters[i].value()._intValue = randomizer.generateRandomNumbers(2, 5);
                                monsters[i].value().resetTimer();
                            }
                            break;
                        case SPRITES::SUPER_MONSTER:
                            if (monsters[i].value().getElapsedTime() > monsters[i].value()._intValue) {
                                nested_pair = {
                                    {positions[i].value()._pos_x, positions[i].value()._pos_y},
                                    {ecs::direction::LEFT, ecs::direction::NO_DIRECTION}
                                };

                                shooting_entities.push_back(std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                                    i,
                                    nested_pair,
                                    SPRITES::BABY_PROJECTILE
                                ));

                                monsters[i].value()._intValue = randomizer.generateRandomNumbers(2, 5);
                                monsters[i].value().resetTimer();
                            }
                            break;
                        case SPRITES::MEGA_MONSTER:
                            if (monsters[i].value().getElapsedTime() > monsters[i].value()._intValue) {
                                std::pair<std::pair<float, float>, std::pair<float, float>> nested_pair = {
                                    {positions[i].value()._pos_x, positions[i].value()._pos_y},
                                    {ecs::direction::LEFT, ecs::direction::NO_DIRECTION}
                                };
                                shooting_entities.push_back(std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                                    i,
                                    nested_pair,
                                    SPRITES::FIRE_BALL
                                ));
                                nested_pair.second = std::make_pair(ecs::direction::LEFT, ecs::direction::UP);
                                shooting_entities.push_back(std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                                    i,
                                    nested_pair,
                                    SPRITES::FIRE_BALL
                                ));
                                nested_pair.second = std::make_pair(ecs::direction::LEFT, ecs::direction::DOWN);
                                shooting_entities.push_back(std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                                    i,
                                    nested_pair,
                                    SPRITES::FIRE_BALL
                                ));

                                monsters[i].value()._intValue = randomizer.generateRandomNumbers(2, 5);
                                monsters[i].value().resetTimer();
                            }
                            break;
                        case SPRITES::SIMPLE_BOSS:
                            if (monsters[i].value().getElapsedTime() > monsters[i].value()._intValue) {
                                shooting_entities.push_back(createEntity(i, positions[i].value()._pos_x + 120, positions[i].value()._pos_y + 320, ecs::direction::LEFT, ecs::direction::DOWN, SPRITES::BOSS_PROJECTILE));
                                shooting_entities.push_back(createEntity(i, positions[i].value()._pos_x + 120, positions[i].value()._pos_y + 350, ecs::direction::LEFT, ecs::direction::NO_DIRECTION, SPRITES::BOSS_PROJECTILE));
                                shooting_entities.push_back(createEntity(i, positions[i].value()._pos_x + 280, positions[i].value()._pos_y + 920, ecs::direction::LEFT, ecs::direction::UP, SPRITES::BOSS_PROJECTILE));
                                shooting_entities.push_back(createEntity(i, positions[i].value()._pos_x + 330, positions[i].value()._pos_y + 520, ecs::direction::LEFT, ecs::direction::NO_DIRECTION, SPRITES::BOSS_PROJECTILE));
                                if (healthes[i].value()._health < 2500) {
                                    if (randomizer.generateRandomNumbers(0, 1) == 0) {
                                        for (int n = 1; n <= 4; n++) {
                                            shooting_entities.push_back(createEntity(i, window_width - (window_width / 4) + (50 * n), window_height - (100 * n), ecs::direction::LEFT, ecs::direction::NO_DIRECTION, SPRITES::BOSS_PROJECTILE));
                                        }
                                    } else {
                                        for (int n = 1; n <= 4; n++) {
                                            shooting_entities.push_back(createEntity(i, window_width - (window_width / 4) + (50 * n), window_height - (100 * n), ecs::direction::LEFT, ecs::direction::UP, SPRITES::BOSS_PROJECTILE));
                                        }
                                    }
                                }

                                monsters[i].value()._intValue = randomizer.generateRandomNumbers(1, 3);
                                monsters[i].value().resetTimer();
                            }
                            break;
                        default:
                            break;
                        }
                    }
                }
                return shooting_entities;
            }

        protected:
        private:
            std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES> createEntity(size_t index, float x, float y, ecs::direction _x, ecs::direction _y, SPRITES sprite) {

                std::pair<std::pair<float, float>, std::pair<float, float>> nested_pair;

                nested_pair.first = std::make_pair(x, y);
                nested_pair.second = std::make_pair(_x, _y);

                return std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>(
                    index,
                    nested_pair,
                    sprite
                );
            }
        };
    }

#endif /* !SHOOTINGSYSTEM_HPP_ */

