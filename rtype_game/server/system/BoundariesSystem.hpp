/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BoundariesSystem
*/

#ifndef BOUNDARIESSYSTEM_HPP_
    #define BOUNDARIESSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/components/Velocity.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../components/Projectiles.hpp"
    #include "../components/Monster.hpp"

    namespace rtype
    {
        class BoundariesSystem {
            public:
                BoundariesSystem() {}
                ~BoundariesSystem() {}

                std::list<size_t> checkAndKillEntities(ecs::ECS &ecs, float windowWidth, float windowHeight)
                    {
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
                        std::list<size_t> dead_entities;

                        for (size_t i = 0; i < positions.size(); ++i)
                        {
                            if (positions[i].has_value())
                            {
                                auto &position = positions[i].value();

                                if (position._pos_x > (windowWidth + 100) || position._pos_y > windowHeight ||
                                    position._pos_x < 0 || position._pos_y < 0)
                                {
                                    std::cout << "KILLL" << std::endl;
                                    ecs.killEntityFromRegistry<ecs::Position>(i);
                                    ecs.killEntityFromRegistry<ecs::Velocity>(i);
                                    ecs.killEntityFromRegistry<Health>(i);
                                    ecs.killEntityFromRegistry<Projectiles>(i);
                                    ecs.killEntityFromRegistry<Hitbox>(i);
                                    ecs.killEntityFromRegistry<Allies>(i);
                                    ecs.killEntityFromRegistry<Ennemies>(i);
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
#endif /* !BOUNDARIESSYSTEM_HPP_ */
