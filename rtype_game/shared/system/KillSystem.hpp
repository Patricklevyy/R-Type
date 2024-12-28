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
    #include "../../client/components/Window.hpp"
    #include "../../client/components/Displayable.hpp"
    #include "../../client/components/Shader.hpp"
    #include "../../client/components/Sprite.hpp"
    #include "../../client/components/Music.hpp"
    #include "../../server/components/SpriteId.hpp"

    namespace rtype
    {
        class KillSystem {
            public:
                KillSystem() {}
                ~KillSystem() {}

                void killEntity(ecs::ECS &ecs, size_t index)
                {
                    // ECS COMPONENTS

                    ecs.killEntityFromRegistry<ecs::Position>(index);
                    ecs.killEntityFromRegistry<ecs::Velocity>(index);
                    ecs.killEntityFromRegistry<ecs::Direction>(index);
                    ecs.killEntityFromRegistry<ecs::Playable>(index);

                    // CLIENT COMPONENTS

                    ecs.killEntityFromRegistry<Displayable>(index);
                    ecs.killEntityFromRegistry<Shader>(index);
                    ecs.killEntityFromRegistry<Sprite>(index);
                    ecs.killEntityFromRegistry<TempDisplay>(index);
                    ecs.killEntityFromRegistry<Window>(index);
                    ecs.killEntityFromRegistry<Music>(index);

                    // SHARED COMPONENTS

                    ecs.killEntityFromRegistry<Health>(index);
                    ecs.killEntityFromRegistry<Levels>(index);

                    // SERVER COMPONENTS

                    ecs.killEntityFromRegistry<Allies>(index);
                    ecs.killEntityFromRegistry<Ennemies>(index);
                    ecs.killEntityFromRegistry<Hitbox>(index);
                    ecs.killEntityFromRegistry<Monster>(index);
                    ecs.killEntityFromRegistry<Projectiles>(index);
                    ecs.killEntityFromRegistry<SpriteId>(index);

                    ecs.addDeadEntity(index);
                }

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
                                killEntity(ecs, i);
                                dead_entities.push_front(i);
                            }
                        }
                    for (size_t i = 0; i < levels.size(); ++i)
                        {
                            if (levels[i].has_value())
                            {
                                killEntity(ecs, i);
                                dead_entities.push_front(i);
                            }
                        }
                    for (size_t i = 0; i < projectiles.size(); ++i)
                        {
                            if (projectiles[i].has_value())
                            {
                                killEntity(ecs, i);
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
                                killEntity(ecs, i);
                            }
                        }
                }

            protected:
            private:
        };
    }
#endif /* !KILLSYSTEM_HPP_ */

