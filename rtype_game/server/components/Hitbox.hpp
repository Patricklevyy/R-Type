/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hitbox
*/

#ifndef HITBOX_HPP_
    #define HITBOX_HPP_

    #include <iostream>

    namespace rtype {
        class Hitbox {
            public:

                Hitbox(std::pair<int, int> x_y) : _width(x_y.first), _height(x_y.second) {};
                ~Hitbox() {};

                int _width;
                int _height;
            protected:
            private:
        };
    }

#endif /* !HITBOX_HPP_ */
