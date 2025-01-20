/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** VelocitySystem
*/

/**
 * @file VelocitySystem.hpp
 * @brief Handles velocity updates for entities in the ECS framework.
 */

#ifndef VELOCITYSYSTEM_HPP_
#define VELOCITYSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/components/Velocity.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../../ecs/components/Playable.hpp"
    #include "../PocExceptions.hpp"

    namespace poc_game
    {
        /**
         * @class PositionSystem
         * @brief Handles position updates for entities in the ECS framework.
         */
        class VelocitySystem
        {
        public:
            /**
             * @brief Updates the velocity of the player in the game.
             *
             * This function updates the velocity of the player by iterating through the 
             * playables and velocity components. If a playable component and a corresponding 
             * velocity component are found, the velocity is updated to the specified value.
             *
             * @param components_array A reference to an unordered map containing the components 
             *                         of the entities, indexed by their type.
             * @param vel The new velocity value to be set for the player.
             */
            void updatePlayerVelocity(std::unordered_map<std::type_index, std::any> &components_array, float vel)
            {
                auto &velocity = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array[typeid(ecs::Velocity)]);
                auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

                for (size_t i = 0; i < playables.size(); ++i)
                    {
                    if (playables[i].has_value() && (i < velocity.size() && velocity[i].has_value()))
                    {
                        velocity[i].value().velocity = vel;
                        return;
                    }
                }
            }

        protected:
        private:
        };
    }

#endif /* !VELOCITYSYSTEM_HPP_ */
