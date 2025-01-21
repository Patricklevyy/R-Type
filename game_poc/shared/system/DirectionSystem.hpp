/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DirectionSystem
*/

/**
 * @file DirectionSystem.hpp
 * @brief Updates the direction of entities in the game.
 */

#ifndef DIRECTIONSYSTEM_HPP_
    #define DIRECTIONSYSTEM_HPP_

    #include "../../../ecs/Includes_ecs.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../../ecs/components/Playable.hpp"

    namespace poc_game
    {
        /**
         * @class DirectionSystem
         * @brief A class that handles the Direction.
         */
        class DirectionSystem
        {
        public:
            /**
             * @brief Updates the direction of a player entity based on the given x and y directions.
             * @param components_array The array of components for the ECS.
             * @param x The x-direction value to update.
             * @param y The y-direction value to update.
             * @param index_player The index of the player entity in the ECS.
             */
            void updatePlayerDirection(std::unordered_map<std::type_index, std::any> &components_array, ecs::direction y)
            {
                auto &direction = std::any_cast<ecs::SparseArray<ecs::Direction> &>(components_array[typeid(ecs::Direction)]);
                auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

                for (size_t i = 0; i < playables.size(); ++i)
                    {
                    if (playables[i].has_value() && (i < direction.size() && direction[i].has_value()))
                    {
                        direction[i].value()._y = y;
                        std::cout << "JUMPPPPPP " << std::endl;
                        return;
                    }
                }
            }

        protected:
        private:
        };
    }
#endif /* !DIRECTIONSYSTEM_HPP_ */
