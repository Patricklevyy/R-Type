/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Direction
*/

/**
 * @file Direction.hpp
 * @brief Defines the Direction component used for managing directional movement.
 */

#ifndef DIRECTION_HPP_
    #define DIRECTION_HPP_

    #include "../Enums_ecs.hpp"

    namespace ecs
    {
        /**
         * @class Direction
         * @brief Represents a 2D direction with x and y components.
         */
        class Direction
        {
        public:
            /**
             * @brief Default constructor for Direction.
             */
            Direction(direction x = direction::NO_DIRECTION, direction y = direction::NO_DIRECTION) : _x(x), _y(y) {}

            /**
             * @brief Destructor for Direction.
             */
            ~Direction() {}

            /**
             * @brief Direction along the X axis.
             */
            direction _x = direction::NO_DIRECTION;

            /**
             * @brief Direction along the Y axis.
             */
            direction _y = direction::NO_DIRECTION;

        protected:
        private:
        };
    }

#endif /* !DIRECTION_HPP_ */
