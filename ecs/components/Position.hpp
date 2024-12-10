/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position
*/

#ifndef POSITION_HPP_
    #define POSITION_HPP_

    namespace ecs
    {
        class Position
        {
        public:
            Position(float pos_x = 0, float pos_y = 0) : _pos_x(pos_x), _pos_y(pos_y) {}
            ~Position() {}

            float _pos_x;
            float _pos_y;

        protected:
        private:
        };
    }

#endif /* !POSITION_HPP_ */
