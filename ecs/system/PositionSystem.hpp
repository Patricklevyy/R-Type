/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PositionSystem
*/

/**
 * @file PositionSystem.hpp
 * @brief Updates entity positions based on their velocities and directions.
 */

#ifndef POSITIONSYSTEM_HPP_
    #define POSITIONSYSTEM_HPP_

    #include "../Includes_ecs.hpp"
    #include "../Enums_ecs.hpp"
    #include "../components/Entity.hpp"
    #include "../components/Position.hpp"
    #include "../components/Velocity.hpp"
    #include "../components/Direction.hpp"
    #include "../components/Playable.hpp"
    #include "../SparseArray.hpp"

    namespace ecs
    {
        /**
         * @class PositionSystem
         * @brief Handles position updates for entities in the ECS framework.
         */
        class PositionSystem
        {
        public:
            /**
             * @brief Updates the positions of entities based on their velocity and direction.
             * @param components_array A map containing all component arrays.
             * @param tickRate The rate at which the system updates (used for time scaling).
             */
            void updatePositions(std::unordered_map<std::type_index, std::any> &components_array, float tickRate)
            {
                auto &positions = std::any_cast<SparseArray<Position> &>(components_array[typeid(Position)]);
                auto &velocities = std::any_cast<SparseArray<Velocity> &>(components_array[typeid(Velocity)]);
                auto &directions = std::any_cast<SparseArray<Direction> &>(components_array[typeid(Direction)]);

                static_assert(std::is_same_v<decltype(positions.size()), std::size_t>, "positions.size() is not std::size_t");
                static_assert(std::is_same_v<decltype(velocities.size()), std::size_t>, "velocities.size() is not std::size_t");
                static_assert(std::is_same_v<decltype(directions.size()), std::size_t>, "directions.size() is not std::size_t");

                std::size_t maxEntities = std::max(
                    static_cast<std::size_t>(positions.size()),
                    std::max(
                        static_cast<std::size_t>(velocities.size()),
                        static_cast<std::size_t>(directions.size())));

                for (std::size_t i = 0; i < maxEntities; ++i)
                {
                    if ((i < positions.size() && positions[i].has_value()) && (i < velocities.size() && velocities[i].has_value()) && (i < directions.size() && directions[i].has_value() && (directions[i].value()._x != direction::NO_DIRECTION || directions[i].value()._y != direction::NO_DIRECTION)))
                    {
                        switch (directions[i].value()._x)
                        {
                        case direction::LEFT:
                            positions[i].value()._pos_x -= velocities[i].value().velocity / tickRate;;
                            break;
                        case direction::RIGHT:
                            positions[i].value()._pos_x += velocities[i].value().velocity / tickRate;
                            break;
                        default:
                            break;
                        }
                        switch (directions[i].value()._y)
                        {
                        case direction::LEFT:
                            positions[i].value()._pos_y -= velocities[i].value().velocity / tickRate;
                            break;
                        case direction::RIGHT:
                            positions[i].value()._pos_y += velocities[i].value().velocity / tickRate;
                            break;
                        default:
                            break;
                        }
                    }
                    else
                    {
                        std::cout << "  Position: None" << std::endl;
                    }
                }
            }

        protected:
        private:
        };
    }
#endif /* !POSITIONSYSTEM_HPP_ */
