/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

/**
 * @file Position.hpp
 * @brief Defines the Position component for 2D positioning.
 */

#ifndef POSITION_HPP_
    #define POSITION_HPP_

    namespace ecs
    {
        /**
         * @class Position
         * @brief Represents a 2D position with X and Y coordinates.
         */
        class Position
        {
        public:
            /**
             * @brief Constructs a Position with initial X and Y coordinates.
             * @param pos_x Initial X coordinate (default: 0).
             * @param pos_y Initial Y coordinate (default: 0).
             */
            Position(float pos_x = 0, float pos_y = 0) : _pos_x(pos_x), _pos_y(pos_y) {}

            /**
             * @brief Destructor for Position.
             */
            ~Position() {}

            /**
             * @brief X coordinate of the position.
             */
            float _pos_x;

            /**
             * @brief Y coordinate of the position.
             */
            float _pos_y;

        protected:
        private:
        };
    }

#endif /* !POSITION_HPP_ */
