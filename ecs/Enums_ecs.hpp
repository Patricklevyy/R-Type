/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Enums
*/

/**
 * @file Enums_ecs.hpp
 * @brief Define the possible direction of the player or monsters in the game
 */

#ifndef ENUMS_ECS_HPP_
    #define ENUMS_ECS_HPP_

    namespace ecs
    {
        enum direction
        {
            NO_CHANGE = -1,
            NO_DIRECTION,
            UP,
            DOWN,
            LEFT,
            RIGHT
        };
    }

#endif /* !ENUMS_ECS_HPP_ */
