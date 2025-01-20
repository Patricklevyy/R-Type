/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Bonus
*/

/**
 * @file Bonus.hpp
 * @brief Class representing bonus in the game.
 *
 * This class is used to define and manage ally bonus entities in the game.
 */

#ifndef BONUS_HPP_
    #define BONUS_HPP_

    #include "../../shared/Enums.hpp"

    namespace rtype
    {
        class Bonus {
            public:
                /**
                 * @brief Constructor for the Bonus class.
                 */
                Bonus(BONUS type) : _type(type) {}

                /**
                 * @brief Destructor for the Bonus class.
                 */
                ~Bonus() {}

                BONUS _type;

            protected:
            private:
        };
    }

#endif /* !BONUS_HPP_ */
