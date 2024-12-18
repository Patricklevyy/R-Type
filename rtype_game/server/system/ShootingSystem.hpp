/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ShootingSystem
*/

#ifndef SHOOTINGSYSTEM_HPP_
    #define SHOOTINGSYSTEM_HPP_

    #include "../components/Monster.hpp"
    #include "../RandomNumber.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include <list>

    namespace rtype
    {
        class ShootingSystem
        {
        public:
            std::list<std::tuple<size_t, float, float>> monster_shooting(std::unordered_map<std::type_index, std::any> &components_array, RandomNumber randomizer)
            {
                auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(components_array[typeid(Monster)]);
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);

                std::list<std::tuple<size_t, float, float>> shooting_entities;
                for (size_t i = 0; i < monsters.size(); ++i) {
                    if (monsters[i].has_value() && positions[i].has_value()) {
                        std::cout << "HAS VALUE " << std::endl;
                        if (monsters[i].value().getElapsedTime() > monsters[i].value()._intValue) {
                            shooting_entities.push_back(std::tuple<size_t, float, float>(i, positions[i].value()._pos_x, positions[i].value()._pos_y));
                            monsters[i].value()._intValue = randomizer.generateRandomNumbers(2, 5);
                            monsters[i].value().resetTimer();
                        }
                    }
                }
            }

        protected:
        private:
        };
    }

#endif /* !SHOOTINGSYSTEM_HPP_ */

