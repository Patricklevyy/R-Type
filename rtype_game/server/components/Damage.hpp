/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Damage
*/

/**
 * @file Damage.hpp
 * @brief Header file for the Damage class.
 *
 * This file defines the `Damage` class, which represents the damage value
 * that an entity or object can inflict. It contains the amount of damage, with
 * a default value of 20.
 */

#ifndef DAMAGE_HPP_
    #define DAMAGE_HPP_

namespace rtype
{
    /**
     * @class Damage
     * @brief A class representing the amount of damage.
     *
     * The `Damage` class stores the damage value inflicted by an entity or object
     * in the game. This class allows the amount of damage to be set and accessed,
     * and has a default damage value of 20.
     */
    class Damage {
        public:
            /**
             * @brief Constructor for the Damage class.
             *
             * Initializes the `Damage` object with a specific amount of damage.
             * If no value is provided, it will default to 20.
             *
             * @param damages The amount of damage (default value is 20).
             */
            Damage(int damages = 20) : _damages(damages) {}

            /**
             * @brief Destructor for the Damage class.
             */
            ~Damage() {}

            /**
             * @brief The amount of damage.
             *
             * This member variable holds the damage value for an entity.
             * It represents the damage value caused by actions like attacks.
             */
            int _damages;

        protected:
        private:
    };
}

#endif /* !DAMAGE_HPP_ */
