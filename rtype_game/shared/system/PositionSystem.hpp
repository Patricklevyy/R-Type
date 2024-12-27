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

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/components/Velocity.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../../ecs/components/Playable.hpp"
    #include "../RTypeExceptions.hpp"

    namespace rtype
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
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);
                auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array[typeid(ecs::Velocity)]);
                auto &directions = std::any_cast<ecs::SparseArray<ecs::Direction> &>(components_array[typeid(ecs::Direction)]);
                auto &playable = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

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
                    if ((i < positions.size() && positions[i].has_value()) && (i < velocities.size() && velocities[i].has_value()) && (i < directions.size() && directions[i].has_value() && (directions[i].value()._x != ecs::direction::NO_DIRECTION || directions[i].value()._y != ecs::direction::NO_DIRECTION)))
                    {
                        switch (directions[i].value()._x)
                        {
                        case ecs::direction::LEFT:
                            if (i < playable.size() && playable[i].has_value() && ((positions[i].value()._pos_x - velocities[i].value().velocity / tickRate) < BORDER_MARGIN)) {
                                break;
                            }
                            positions[i].value()._pos_x -= velocities[i].value().velocity / tickRate;
                            break;
                        case ecs::direction::RIGHT:
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
                        case ecs::direction::UP:
                            if (i < playable.size() && playable[i].has_value() && ((positions[i].value()._pos_y - velocities[i].value().velocity / tickRate) < BORDER_MARGIN)) {
                                break;
                            }
                            positions[i].value()._pos_y -= velocities[i].value().velocity / tickRate;
                            break;
                        case ecs::direction::DOWN:
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

            /**
            * @brief Updates the position of a player based on their velocity and direction.
            *
            * This function updates the x and y coordinates of the player's position
            * based on their current velocity, direction, and the tick rate. The player's
            * movement is constrained by the boundaries of the window dimensions.
            *
            * @param components_array A reference to a map containing component arrays,
            *                         with each component identified by its type.
            * @param tickRate The rate at which updates occur (ticks per second).
            * @param indexPlayer The index of the player in the components array.
            * @param window_width The width of the window boundary.
            * @param window_height The height of the window boundary.
            */
            void updatePlayerPositions(std::unordered_map<std::type_index, std::any> &components_array, float tickRate, int indexPlayer, int window_width, int window_height)
            {
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);
                auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array[typeid(ecs::Velocity)]);
                auto &directions = std::any_cast<ecs::SparseArray<ecs::Direction> &>(components_array[typeid(ecs::Direction)]);

                if (indexPlayer == -1 || !directions[indexPlayer].has_value() || !velocities[indexPlayer].has_value() || !positions[indexPlayer].has_value())
                    return;
                std::cout << "PLAYER POS " << positions[indexPlayer].value()._pos_x << " , " << positions[indexPlayer].value()._pos_y << std::endl;
                switch (directions[indexPlayer].value()._x) {
                    case ecs::direction::LEFT:
                        if ((positions[indexPlayer].value()._pos_x - velocities[indexPlayer].value().velocity / tickRate) < BORDER_MARGIN) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_x -= velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    case ecs::direction::RIGHT:
                        if ((positions[indexPlayer].value()._pos_x + velocities[indexPlayer].value().velocity / tickRate) > (window_width - BORDER_MARGIN * 18)) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_x += velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    default:
                        break;
                    }
                    switch (directions[indexPlayer].value()._y) {
                    case ecs::direction::UP:
                        if ((positions[indexPlayer].value()._pos_y - velocities[indexPlayer].value().velocity / tickRate) < BORDER_MARGIN) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_y -= velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    case ecs::direction::DOWN:
                        if ((positions[indexPlayer].value()._pos_y + velocities[indexPlayer].value().velocity / tickRate) > (window_height - BORDER_MARGIN * 10)) {
                            break;
                        }
                        positions[indexPlayer].value()._pos_y += velocities[indexPlayer].value().velocity / tickRate;
                        break;
                    default:
                        break;
                    }
            }

            /**
             * @brief Retrieves the position of a player from the ECS.
             *
             * This function returns the x and y coordinates of a player's position.
             * If the player does not exist in the ECS, an exception is thrown.
             *
             * @param index The index of the player in the components array.
             * @param components_array A reference to a map containing component arrays,
             *                         with each component identified by its type.
             * @return A pair of floats representing the x and y coordinates of the player's position.
             * @throws ERROR::PlayerNotFoundInEcs If the player is not found in the ECS.
             */
            std::pair<float, float> getPlayerPosition(size_t index, std::unordered_map<std::type_index, std::any> &components_array)
            {
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);

                if (positions[index].has_value())
                    return std::pair<float, float>(positions[index].value()._pos_x, positions[index].value()._pos_y);
                throw ERROR::PlayerDontExistInEcsException("NO player found in ECS");
            }

        protected:
        private:
        };
    }
#endif /* !POSITIONSYSTEM_HPP_ */
