/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KillSystem
*/

#ifndef KILLSYSTEM_HPP_
    #define KILLSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/components/Velocity.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../../server/components/Projectiles.hpp"
    #include "../../server/components/Allies.hpp"
    #include "../../server/components/Ennemies.hpp"
    #include "../../server/components/Monster.hpp"
    #include "../../server/components/Hitbox.hpp"
    #include "../components/Levels.hpp"
    #include "../../client/components/TempDisplay.hpp"
    #include "../../client/components/Displayable.hpp"
    #include "../../server/components/SpriteId.hpp"

    namespace rtype
    {
        class KillSystem {
            public:
                KillSystem() {}
                ~KillSystem() {}

                std::list<size_t> killMonstersAndProjectiles(ecs::ECS &ecs)
                {
                    auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(ecs._components_arrays[typeid(Levels)]);
                    auto &projectiles = std::any_cast<ecs::SparseArray<Projectiles> &>(ecs._components_arrays[typeid(Projectiles)]);

                    std::list<size_t> dead_entities;

                    for (size_t i = 0; i < monsters.size(); ++i)
                        {
                            if (monsters[i].has_value())
                            {
                                ecs.killEntityFromRegistry<ecs::Direction>(i);
                                ecs.killEntityFromRegistry<ecs::Position>(i);
                                ecs.killEntityFromRegistry<ecs::Velocity>(i);
                                ecs.killEntityFromRegistry<Health>(i);
                                ecs.killEntityFromRegistry<Projectiles>(i);
                                ecs.killEntityFromRegistry<SpriteId>(i);
                                ecs.killEntityFromRegistry<Hitbox>(i);
                                ecs.killEntityFromRegistry<Allies>(i);
                                ecs.killEntityFromRegistry<Ennemies>(i);
                                ecs.addDeadEntity(i);
                                dead_entities.push_front(i);
                            }
                        }
                    for (size_t i = 0; i < levels.size(); ++i)
                        {
                            if (levels[i].has_value())
                            {
                                ecs.killEntityFromRegistry<ecs::Direction>(i);
                                ecs.killEntityFromRegistry<Levels>(i);
                                ecs.killEntityFromRegistry<ecs::Position>(i);
                                ecs.killEntityFromRegistry<ecs::Velocity>(i);
                                ecs.killEntityFromRegistry<Health>(i);
                                ecs.killEntityFromRegistry<Projectiles>(i);
                                ecs.killEntityFromRegistry<SpriteId>(i);
                                ecs.killEntityFromRegistry<Hitbox>(i);
                                ecs.killEntityFromRegistry<Allies>(i);
                                ecs.killEntityFromRegistry<Ennemies>(i);
                                ecs.addDeadEntity(i);
                                dead_entities.push_front(i);
                            }
                        }
                    for (size_t i = 0; i < projectiles.size(); ++i)
                        {
                            if (projectiles[i].has_value())
                            {
                                ecs.killEntityFromRegistry<ecs::Direction>(i);
                                ecs.killEntityFromRegistry<Displayable>(i);
                                ecs.killEntityFromRegistry<ecs::Position>(i);
                                ecs.killEntityFromRegistry<ecs::Velocity>(i);
                                ecs.killEntityFromRegistry<Health>(i);
                                ecs.killEntityFromRegistry<Projectiles>(i);
                                ecs.killEntityFromRegistry<SpriteId>(i);
                                ecs.killEntityFromRegistry<Hitbox>(i);
                                ecs.killEntityFromRegistry<Allies>(i);
                                ecs.killEntityFromRegistry<Ennemies>(i);
                                ecs.addDeadEntity(i);
                                dead_entities.push_front(i);
                            }
                        }
                    return dead_entities;
                }

                void killTempDisplay(ecs::ECS &ecs)
                {
                    auto &tempdisplays = std::any_cast<ecs::SparseArray<TempDisplay> &>(ecs._components_arrays[typeid(TempDisplay)]);

                    for (size_t i = 0; i < tempdisplays.size(); ++i)
                        {
                            if (tempdisplays[i].has_value())
                            {
                                ecs.killEntityFromRegistry<ecs::Direction>(i);
                                ecs.killEntityFromRegistry<ecs::Position>(i);
                                ecs.killEntityFromRegistry<ecs::Velocity>(i);
                                ecs.killEntityFromRegistry<Health>(i);
                                ecs.killEntityFromRegistry<Projectiles>(i);
                                ecs.killEntityFromRegistry<SpriteId>(i);
                                ecs.killEntityFromRegistry<Hitbox>(i);
                                ecs.killEntityFromRegistry<Allies>(i);
                                ecs.killEntityFromRegistry<Ennemies>(i);
                                ecs.killEntityFromRegistry<TempDisplay>(i);
                                ecs.killEntityFromRegistry<Displayable>(i);
                                ecs.addDeadEntity(i);
                            }
                        }
                }

            protected:
            private:
        };
    }
#endif /* !KILLSYSTEM_HPP_ */

