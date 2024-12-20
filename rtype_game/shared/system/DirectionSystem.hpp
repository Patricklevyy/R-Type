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

    namespace rtype
    {
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
            void updatePlayerDirection(std::unordered_map<std::type_index, std::any> &components_array, ecs::direction x, ecs::direction y, size_t index_player)
            {
                auto &direction = std::any_cast<ecs::SparseArray<ecs::Direction> &>(components_array[typeid(ecs::Direction)]);

                if (index_player < direction.size() && direction[index_player].has_value()) {
                    if (ecs::direction::NO_CHANGE != x)
                        direction[index_player].value()._x = x;
                    if (ecs::direction::NO_CHANGE != y)
                        direction[index_player].value()._y = y;
                    return;
                }
            }

        protected:
        private:
        };
    }
#endif /* !DIRECTIONSYSTEM_HPP_ */
