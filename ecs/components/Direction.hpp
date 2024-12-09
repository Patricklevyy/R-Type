/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Direction
*/

#ifndef DIRECTION_HPP_
    #define DIRECTION_HPP_

    #include "../Enums_ecs.hpp"

    namespace ecs
    {
        class Direction
        {
        public:
            Direction() {}
            ~Direction() {}

            direction _x = direction::NO_DIRECTION;
            direction _y = direction::NO_DIRECTION;

        protected:
        private:
        };
    }

#endif /* !DIRECTION_HPP_ */
