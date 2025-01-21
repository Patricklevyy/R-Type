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

    namespace rtype {
        /**
         * @class Hitbox
         * @brief A class that handles Hitbox of entities in the game.
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

                /**
                 * @brief Set the hitbox of an entity.
                 * @param x_y a pair that represent the location of the entity to set it hitbox
                 */
                void setHitbox(std::pair<int, int> x_y) {
                    _width = x_y.first;
                    _height = x_y.second;
                }

                int _width;
                int _height;
                bool _invicible = false;
            protected:
            private:
        };
    }

#endif /* !HITBOX_HPP_ */
