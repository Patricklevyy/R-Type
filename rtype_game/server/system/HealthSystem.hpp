/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HealthSystem
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

    namespace rtype
    {
        class HealthSystem {
            public:
                HealthSystem() {}
                ~HealthSystem() {}

                std::tuple<std::list<size_t>, unsigned int, bool> checkAndKillEntities(ecs::ECS &ecs, unsigned int &player_alive)
                    {
                        auto &healths = std::any_cast<ecs::SparseArray<Health> &>(ecs._components_arrays[typeid(Health)]);
                        auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(ecs._components_arrays[typeid(ecs::Playable)]);
                        std::tuple<std::list<size_t>, unsigned int, bool> dead_entities;
                        std::get<1>(dead_entities) = 0;
                        std::get<2>(dead_entities) = false;

                        for (size_t i = 0; i < healths.size(); ++i)
                        {
                            if (healths[i].has_value())
                            {
                                auto &health = healths[i].value();

                                if (health._health <= 0)
                                {
                                    std::cout << "KILLL, deaddddd" << std::endl;
                                    if (i < monsters.size() && monsters[i].has_value())
                                        std::get<1>(dead_entities)++;
                                    if (i < playables.size() && playables[i].has_value()) {
                                        player_alive--;
                                        if (player_alive <= 0)
                                            std::get<2>(dead_entities) = true;
                                    }
                                    ecs.killEntityFromRegistry<ecs::Position>(i);
                                    ecs.killEntityFromRegistry<ecs::Playable>(i);
                                    ecs.killEntityFromRegistry<Hitbox>(i);
                                    ecs.killEntityFromRegistry<ecs::Velocity>(i);
                                    ecs.killEntityFromRegistry<Health>(i);
                                    ecs.killEntityFromRegistry<Monster>(i);
                                    ecs.killEntityFromRegistry<ecs::Direction>(i);
                                    ecs.killEntityFromRegistry<Ennemies>(i);
                                    ecs.killEntityFromRegistry<Allies>(i);
                                    ecs.addDeadEntity(i);
                                    std::get<0>(dead_entities).push_front(i);
                                }
                            }
                        }
                        return dead_entities;
                    }

            protected:
            private:
        };

    }

#endif /* !HEALTHSYSTEM_HPP_ */
