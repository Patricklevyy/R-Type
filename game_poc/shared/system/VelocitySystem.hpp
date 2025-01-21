/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** VelocitySystem
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
             * @brief Updates the velocity of the player.
             * @param components_array The unordered map of all components in the ECS
             * @param vel The new velocity value to set for the player.
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
