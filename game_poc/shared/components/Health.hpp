/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Health
*/

/**
 * @file Health.hpp
 * @brief Class representing the component heath in the game.
 *
 * This class is used to define the health of the monster, the player and the missile
 */

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

namespace poc_game {

    class Health {
        public:
            /**
             * @brief Constructor for the Health class.
             */
            Health(int health) : _health(health){};

            /**
             * @brief Destructor for the Ennemies class.
             */
            ~Health() {};

            int _health;

        protected:
        private:
    };
}

#endif /* !HEALTH_HPP_ */
