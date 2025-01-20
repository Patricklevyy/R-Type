/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem
*/

/**
 * @file HealthSystem.hpp
 * @brief Handles health management and entity removal upon health depletion.
 */

#ifndef HEALTHSYSTEM_HPP_
    #define HEALTHSYSTEM_HPP_

    #include "../../shared/components/Health.hpp"
    #include "../../../ecs/ECS.hpp"
    #include <iostream>
    #include <list>
    #include "../components/Monster.hpp"
    #include "../components/Hitbox.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../../ecs/components/Playable.hpp"
    #include "../../../ecs/components/Position.hpp"

    namespace rtype
    {
        /**
        * @class HealthSystem
        * @brief Manages entity health and removes entities with zero or negative health.
        */
        class HealthSystem {
            public:

                /**
                 * @brief Constructor for HealthSystem.
                 */
                HealthSystem() {}

                /**
                 * @brief Destructor for HealthSystem.
                 */
                ~HealthSystem() {}

                std::tuple<std::list<size_t>, unsigned int, bool, std::list<std::pair<float, float>>> checkLife(ecs::ECS &ecs, unsigned int &player_alive)
                // std::tuple<std::list<size_t>, unsigned int, bool> checkLife(ecs::ECS &ecs, unsigned int &player_alive)
                    {
                        auto &healths = std::any_cast<ecs::SparseArray<Health> &>(ecs._components_arrays[typeid(Health)]);
                        auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(ecs._components_arrays[typeid(ecs::Playable)]);
                        // std::tuple<std::list<size_t>, unsigned int, bool> dead_entities;
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
                        std::tuple<std::list<size_t>, unsigned int, bool, std::list<std::pair<float, float>>> dead_entities;
                        std::get<1>(dead_entities) = 0;
                        std::get<2>(dead_entities) = false;

                        for (size_t i = 0; i < healths.size(); ++i)
                        {
                            if (healths[i].has_value())
                            {
                                auto &health = healths[i].value();

                                if (health._health <= 0)
                                {
                                    if (i < monsters.size() && monsters[i].has_value())
                                        std::get<1>(dead_entities) += monsters[i].value()._score_value;
                                    if (i < playables.size() && playables[i].has_value()) {
                                        player_alive--;
                                        if (player_alive <= 0)
                                            std::get<2>(dead_entities) = true;
                                    }
                                    std::get<0>(dead_entities).push_front(i);
                                    if (i < positions.size() && positions[i].has_value()) {
                                        auto &pos = positions[i].value();
                                        std::get<3>(dead_entities).push_front({pos._pos_x, pos._pos_y});
                                    }
                                }
                            }
                        }
                        return dead_entities;
                    }

                    std::list<std::pair<size_t, int>> updatePlayerLife(std::unordered_map<std::type_index, std::any> &components_array) {

                        auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

                        std::list<std::pair<size_t, int>> lifes_updates;

                        static auto last_execution_time = std::chrono::steady_clock::now();

                        auto now = std::chrono::steady_clock::now();
                        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_execution_time);
                        if (elapsed.count() < 500) {
                            return lifes_updates;
                        }

                        last_execution_time = now;


                        for (size_t i = 0; i < playables.size(); ++i)
                        {
                            if (playables[i].has_value() && i < healths.size() && healths[i].has_value())
                            {
                                lifes_updates.push_front(std::make_pair(i, healths[i].value()._health));
                            }
                        }
                        return lifes_updates;
                    }

            protected:
            private:
        };

    }

#endif /* !HEALTHSYSTEM_HPP_ */
