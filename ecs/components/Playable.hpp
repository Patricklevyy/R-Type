/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Playable
*/

/**
 * @file Playable.hpp
 * @brief Defines the Playable component, representing a playable entity.
 */

#ifndef PLAYABLE_HPP_
    #define PLAYABLE_HPP_

    namespace ecs
    {
        /**
         * @class Playable
         * @brief Represents a playable entity in the game.
         */
        class Playable
        {
        public:
            /**
             * @brief Constructs a Playable entity with a given name.
             * @param name Name of the playable entity (default: empty string).
             */
            Playable(std::string name = "") : _name(name) {}

            /**
             * @brief Destructor for Playable.
             */
            ~Playable() {}

            /**
             * @brief Name of the playable entity.
             */
            std::string _name;

        protected:
        private:
        };
    }

#endif /* !PLAYABLE_HPP_ */
