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
    #include "../RandomNumber.hpp"
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
            std::list<std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>> monster_shooting(std::unordered_map<std::type_index, std::any> &components_array, RandomNumber randomizer)
            {
                auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(components_array[typeid(Monster)]);
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);

                std::list<std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>> shooting_entities;
                std::pair<std::pair<float, float>, std::pair<float, float>> nested_pair;
                for (size_t i = 0; i < monsters.size(); ++i) {
                    if (monsters[i].has_value() && positions[i].has_value()) {
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
                        default:
                            break;
                        }
                    }
                }
                return shooting_entities;
            }

        protected:
        private:
        };
    }

#endif /* !SHOOTINGSYSTEM_HPP_ */

