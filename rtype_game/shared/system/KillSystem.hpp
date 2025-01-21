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
    #include "../../server/components/Bonus.hpp"
    #include "../../server/components/Hitbox.hpp"
    #include "../../server/components/Damage.hpp"
    #include "../../server/components/PowerUp.hpp"
    #include "../components/Levels.hpp"
    #include "../../client/components/LevelStatus.hpp"
    #include "../../client/components/Animation.hpp"
    #include "../../client/components/Window.hpp"
    #include "../../client/components/Displayable.hpp"
    #include "../../client/components/Shader.hpp"
    #include "../../client/components/Sprite.hpp"
    #include "../../client/components/Music.hpp"
    #include "../../server/components/SpriteId.hpp"
    #include "../../server/components/Bonus.hpp"
    #include "../../client/components/Text.hpp"
    #include "../../client/components/Life.hpp"

    namespace rtype
    {
        /**
         * @class KillSystem
         * @brief A class that handles the kills in the game.
         *
         * The KillSystem class is managing every kill entity
         */
        class KillSystem {
            public:
                /**
                 * @brief Constructor for the KillSystem class.
                 */
                KillSystem() {}

                /**
                 * @brief Destructor for the KillSystem class.
                 */
                ~KillSystem() {}

                /**
                 * @brief Kill the entity when it has taken too much damage.
                 * @param ecs A reference to the ECS (Entity Component System) managing all components and entities.
                 *        It allows access to the components of the entity being processed.
                 * @param index The index of the player entity whose life is to be updated.
                 */
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
                    ecs.killEntityFromRegistry<LevelStatus>(index);
                    ecs.killEntityFromRegistry<Window>(index);
                    ecs.killEntityFromRegistry<Music>(index);
                    ecs.killEntityFromRegistry<Text>(index);
                    ecs.killEntityFromRegistry<Animation>(index);
                    ecs.killEntityFromRegistry<Life>(index);

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
                    ecs.killEntityFromRegistry<Bonus>(index);
                    ecs.killEntityFromRegistry<Damage>(index);
                    ecs.killEntityFromRegistry<PowerUp>(index);

                    ecs.addDeadEntity(index);
                }

                /**
                 * @brief Kill all the entity when a stage is done.
                 * @param ecs A reference to the ECS (Entity Component System) managing all components and entities.
                 *        It allows access to the components of the entity being processed.
                 */
                std::list<size_t> killAllExceptPlayer(ecs::ECS &ecs)
                {
                    auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(ecs._components_arrays[typeid(Levels)]);
                    auto &projectiles = std::any_cast<ecs::SparseArray<Projectiles> &>(ecs._components_arrays[typeid(Projectiles)]);
                    auto &bonuses = std::any_cast<ecs::SparseArray<Bonus> &>(ecs._components_arrays[typeid(Bonus)]);

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
                    for (size_t i = 0; i < bonuses.size(); ++i)
                        {
                            if (bonuses[i].has_value())
                            {
                                killEntity(ecs, i);
                                dead_entities.push_front(i);
                            }
                        }
                    return dead_entities;
                }

                /**
                 * @brief Kill the win or loose status.
                 * @param ecs A reference to the ECS (Entity Component System) managing all components and entities.
                 *        It allows access to the components of the entity being processed.
                 */
                void killLevelStatus(ecs::ECS &ecs)
                {
                    auto &level_status = std::any_cast<ecs::SparseArray<LevelStatus> &>(ecs._components_arrays[typeid(LevelStatus)]);

                    for (size_t i = 0; i < level_status.size(); ++i)
                        {
                            if (level_status[i].has_value())
                            {
                                killEntity(ecs, i);
                            }
                        }
                }

                /**
                 * @brief Kill the texts in the window.
                 * @param ecs A reference to the ECS (Entity Component System) managing all components and entities.
                 *        It allows access to the components of the entity being processed.
                 */
                void killTexts(ecs::ECS &ecs)
                {
                    auto &texts = std::any_cast<ecs::SparseArray<Text> &>(ecs._components_arrays[typeid(Text)]);

                    for (size_t i = 0; i < texts.size(); ++i)
                        {
                            if (texts[i].has_value())
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

