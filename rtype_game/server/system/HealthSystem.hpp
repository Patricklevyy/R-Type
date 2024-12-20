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

                /**
                 * @brief Checks the health of entities and removes those with zero or less health.
                 * @param ecs The ECS manager.
                 * @return A list of entities that have been removed.
                 */
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
                                    std::cout << "KILLL, deaddddd" << std::endl;
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
