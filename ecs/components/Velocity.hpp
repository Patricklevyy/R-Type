/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

/**
 * @file Velocity.hpp
 * @brief Defines the Velocity component for movement speed.
 */

#ifndef VELOCITY_HPP_
    #define VELOCITY_HPP_

    namespace ecs
    {
        /**
         * @class Velocity
         * @brief Represents the velocity of an entity.
         */
        class Velocity
        {
        public:
            /**
             * @brief Default constructor for Velocity.
             */
            Velocity(int velocityyyy): velocity(velocityyyy) {}

            /**
             * @brief Destructor for Velocity.
             */
            ~Velocity() {}

            /**
             * @brief Movement speed of the entity.
             * @note Consider making this configurable through an external file.
             */
            float velocity;

        protected:
        private:
        };
    }

#endif /* !VELOCITY_HPP_ */
