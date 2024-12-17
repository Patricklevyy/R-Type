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

    namespace rtype
    {
        class HealthSystem {
            public:
                HealthSystem() {}
                ~HealthSystem() {}

                std::list<size_t> checkAndKillEntities(ecs::ECS &ecs)
                    {
                        auto &healths = std::any_cast<ecs::SparseArray<Health> &>(ecs._components_arrays[typeid(Health)]);
                        std::list<size_t> dead_entities;

                        for (size_t i = 0; i < healths.size(); ++i)
                        {
                            if (healths[i].has_value())
                            {
                                auto &health = healths[i].value();

                                if (health._health <= 0)
                                {
                                    std::cout << "KILLL" << std::endl;
                                    ecs.killEntityFromRegistry<ecs::Position>(i);
                                    ecs.killEntityFromRegistry<ecs::Playable>(i);
                                    ecs.killEntityFromRegistry<Hitbox>(i);
                                    ecs.killEntityFromRegistry<ecs::Velocity>(i);
                                    ecs.killEntityFromRegistry<ecs::Position>(i);
                                    ecs.killEntityFromRegistry<Health>(i);
                                    ecs.killEntityFromRegistry<Monster>(i);
                                    ecs.addDeadEntity(i);
                                    dead_entities.push_front(i);
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
