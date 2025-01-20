/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hitbox
*/

/**
 * @file Hitbox.hpp
 * @brief Class representing enemies in the game.
 *
 * This class is used to define and manage enemy entities in the game.
 */

#ifndef HITBOX_HPP_
    #define HITBOX_HPP_

    #include <iostream>

    namespace poc_game
    {

        /**
         * @class Hitbox
         * @brief Represents the Hitbox class.
         */
        class Hitbox {
            public:

                /**
                 * @brief Constructor for the Ennemies class.
                 */
                Hitbox(std::pair<int, int> x_y) : _width(x_y.first), _height(x_y.second) {};

                /**
                 * @brief Destructor for the Ennemies class.
                 */
                ~Hitbox() {};

                int _width;
                int _height;
            protected:
            private:
        };
    }

#endif /* !HITBOX_HPP_ */
