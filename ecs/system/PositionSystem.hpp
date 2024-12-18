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
    #include "../ECS.hpp"
    namespace ecs
    {
        const float BORDER_MARGIN = 10.0f;
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
            void updatePositions(std::unordered_map<std::type_index, std::any> &components_array, float tickRate, int window_width, int window_height)
            {
                auto &positions = std::any_cast<SparseArray<Position> &>(components_array[typeid(Position)]);
                auto &velocities = std::any_cast<SparseArray<Velocity> &>(components_array[typeid(Velocity)]);
                auto &directions = std::any_cast<SparseArray<Direction> &>(components_array[typeid(Direction)]);
                auto &playable = std::any_cast<SparseArray<Playable> &>(components_array[typeid(Playable)]);

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
                            if (i < playable.size() && playable[i].has_value() && ((positions[i].value()._pos_x - velocities[i].value().velocity / tickRate) < BORDER_MARGIN)) {
                                break;
                            }
                            positions[i].value()._pos_x -= velocities[i].value().velocity / tickRate;
                            break;
                        case direction::RIGHT:
                            if (i < playable.size() && playable[i].has_value() && ((positions[i].value()._pos_x + velocities[i].value().velocity / tickRate) > (window_width - BORDER_MARGIN * 18))) {
                                break;
                            }
                            positions[i].value()._pos_x += velocities[i].value().velocity / tickRate;
                            break;
                        default:
                            break;
                        }
                        switch (directions[i].value()._y)
                        {
                        case direction::UP:
                            if (i < playable.size() && playable[i].has_value() && ((positions[i].value()._pos_y - velocities[i].value().velocity / tickRate) < BORDER_MARGIN)) {
                                break;
                            }
                            positions[i].value()._pos_y -= velocities[i].value().velocity / tickRate;
                            break;
                        case direction::DOWN:
                            if (i < playable.size() && playable[i].has_value() && ((positions[i].value()._pos_y + velocities[i].value().velocity / tickRate) > (window_height - BORDER_MARGIN * 10))) {
                                break;
                            }
                            positions[i].value()._pos_y += velocities[i].value().velocity / tickRate;
                            break;
                        default:
                            break;
                        }
                    }
                }
            }

            void updatePlayerPositions(std::unordered_map<std::type_index, std::any> &components_array, float tickRate, int indexPlayer, int window_width, int window_height)
            {
                if (indexPlayer == -1)
                    return;
                auto &positions = std::any_cast<SparseArray<Position> &>(components_array[typeid(Position)]);
                auto &velocities = std::any_cast<SparseArray<Velocity> &>(components_array[typeid(Velocity)]);
                auto &directions = std::any_cast<SparseArray<Direction> &>(components_array[typeid(Direction)]);

                std::cout << "PLAYER POS " << positions[indexPlayer].value()._pos_x << " , " << positions[indexPlayer].value()._pos_y << std::endl;
                switch (directions[indexPlayer].value()._x) {
                    case direction::LEFT:
                        if ((positions[indexPlayer].value()._pos_x - velocities[indexPlayer].value().velocity / tickRate) < BORDER_MARGIN) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_x -= velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    case direction::RIGHT:
                        if ((positions[indexPlayer].value()._pos_x + velocities[indexPlayer].value().velocity / tickRate) > (window_width - BORDER_MARGIN * 18)) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_x += velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    default:
                        break;
                    }
                    switch (directions[indexPlayer].value()._y) {
                    case direction::UP:
                        if ((positions[indexPlayer].value()._pos_y - velocities[indexPlayer].value().velocity / tickRate) < BORDER_MARGIN) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_y -= velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    case direction::DOWN:
                        if ((positions[indexPlayer].value()._pos_y + velocities[indexPlayer].value().velocity / tickRate) > (window_height - BORDER_MARGIN * 10)) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_y += velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    default:
                        break;
                    }
            }

            std::pair<float, float> getPlayerPosition(size_t index, std::unordered_map<std::type_index, std::any> &components_array)
            {
                auto &positions = std::any_cast<SparseArray<Position> &>(components_array[typeid(Position)]);

                if (positions[index].has_value())
                    return std::pair<float, float>(positions[index].value()._pos_x, positions[index].value()._pos_y);
                throw ERROR::PlayerNotFoundInEcs("NO player found in ECS");
            }

        protected:
        private:
        };
    }
#endif /* !POSITIONSYSTEM_HPP_ */
