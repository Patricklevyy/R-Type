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
    #include "../../server/components/Allies.hpp"
    #include "../../server/components/Ennemies.hpp"
    #include "../../server/components/Hitbox.hpp"
    #include "../components/Levels.hpp"
    #include "../../client/components/TempDisplay.hpp"
    #include "../../client/components/Window.hpp"
    #include "../../client/components/Displayable.hpp"
    #include "../../client/components/Shader.hpp"
    #include "../../client/components/Sprite.hpp"
    #include "../../client/components/Music.hpp"

    namespace poc_game
    {
        /**
         * @class KillSystem
         * @brief A class that handles the kills in the game.
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

                    ecs.addDeadEntity(index);
                }

                /**
                 * @brief Kill temporary the display.
                 * @param ecs A reference to the ECS (Entity Component System) managing all components and entities.
                 */
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

                /**
                 * @brief Kill only pipes when the player passed them correctly.
                 * @param ecs A reference to the ECS (Entity Component System) managing all components and entities.
                 */
                std::list<size_t> killPipes(ecs::ECS &ecs)
                {
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(ecs._components_arrays[typeid(Health)]);

                    std::list<size_t> deads;
                    for (size_t i = 0; i < healths.size(); ++i)
                        {
                            if (healths[i].has_value())
                            {
                                deads.push_front(i);
                            }
                        }
                    return deads;
                }

                /**
                 * @brief Kill all the entity when a stage is done.
                 * @param ecs A reference to the ECS (Entity Component System) managing all components and entities.
                 */
                std::list<size_t> killEverything(ecs::ECS &ecs)
                {
                    auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);

                    std::list<size_t> dead_entities;
                    for (size_t i = 0; i < positions.size(); ++i)
                        {
                            if (positions[i].has_value())
                            {
                                dead_entities.push_front(i);
                                killEntity(ecs, i);
                            }
                        }
                    return dead_entities;
                }

            protected:
            private:
        };
    }
#endif /* !KILLSYSTEM_HPP_ */

