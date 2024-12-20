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
            std::list<std::tuple<size_t, std::pair<float, float>, SPRITES>> monster_shooting(std::unordered_map<std::type_index, std::any> &components_array, RandomNumber randomizer)
            {
                auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(components_array[typeid(Monster)]);
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);

                std::list<std::tuple<size_t, std::pair<float, float>, SPRITES>> shooting_entities;
                for (size_t i = 0; i < monsters.size(); ++i) {
                    if (monsters[i].has_value() && positions[i].has_value()) {
                        std::cout << "HAS VALUE " << std::endl;
                        if (monsters[i].value().getElapsedTime() > monsters[i].value()._intValue) {
                            shooting_entities.push_back(std::tuple<size_t, std::pair<float, float>, SPRITES>(
                                i,
                                {positions[i].value()._pos_x, positions[i].value()._pos_y},
                                SPRITES::MONSTER_SIMPLE_MISSILE
                            ));
                            monsters[i].value()._intValue = randomizer.generateRandomNumbers(2, 5);
                            monsters[i].value().resetTimer();
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

