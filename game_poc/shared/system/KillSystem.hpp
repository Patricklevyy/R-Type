/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KillSystem
*/

/**
 * @file KillSystem.hpp
 * @brief System responsible for killing entities and managing their components.
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
         * @brief Class responsible for managing the removal (killing) of entities in the game.
         * 
         * This class encapsulates logic to remove various game components from entities
         * across all subsystems (client, shared, server) by their unique identifiers (indices).
         */
        class KillSystem {
            public:
                /**
                 * @brief Default constructor for the KillSystem class.
                 */
                KillSystem() {}

                /**
                 * @brief Destructor for the KillSystem class.
                 */
                ~KillSystem() {}

                /**
                 * @brief Removes an entity by its index from the ECS and its associated components.
                 * 
                 * This function calls `killEntityFromRegistry` for each relevant component associated 
                 * with the entity to ensure complete cleanup. It marks the entity as dead.
                 * 
                 * @param ecs Reference to the ECS (Entity Component System) that holds the entities.
                 * @param index The unique index of the entity to remove.
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
                 * @brief Removes all entities that have a temporary display component.
                 * 
                 * This function iterates over all entities that have a `TempDisplay` component and
                 * removes them by calling `killEntity` for each one.
                 * 
                 * @param ecs Reference to the ECS (Entity Component System) that holds the entities.
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
                 * @brief Removes entities based on their health status (e.g., dead).
                 * 
                 * This function checks the health of all entities and if an entity's health is not
                 * valid (indicating that it is dead or should be removed), the entity is queued for
                 * removal by returning the entity's index.
                 * 
                 * @param ecs Reference to the ECS (Entity Component System) that holds the entities.
                 * @return A list of entity indices marked for removal.
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
                 * @brief Removes all entities from the game world.
                 * 
                 * This function iterates over all entities with a `Position` component and removes 
                 * them from the ECS, marking them as dead and clearing their associated components.
                 * 
                 * @param ecs Reference to the ECS (Entity Component System) that holds the entities.
                 * @return A list of entity indices that have been removed.
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
