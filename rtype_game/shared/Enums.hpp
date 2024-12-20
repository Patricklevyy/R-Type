/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Enums
*/

/**
 * @file Enums.hpp
 * @brief Defines various enumerations for actions, sprites, and visual filters in the R-Type game.
 */

#ifndef ENUMS_HPP_
    #define ENUMS_HPP_

    namespace rtype
    {

        /**
         * @enum RTYPE_ACTIONS
         * @brief Defines all the possible actions in the R-Type game.
         */
        enum RTYPE_ACTIONS
        {
            UNDEFINED = -1,
            CREATE_ROOM,
            JOIN_ROOM,
            LEAVE_ROOM,
            MOVE_UP,
            MOVE_UP_STOP,
            MOVE_RIGHT,
            MOVE_RIGHT_STOP,
            MOVE_DOWN,
            MOVE_DOWN_STOP,
            MOVE_LEFT,
            MOVE_LEFT_STOP,
            UPDATE_POSITION,
            CHECK_EVENT_WINDOW,
            CREATE_CLIENT,
            CREATE_TEAMMATE,
            UPDATE_DIRECTION,
            UPDATE_PLAYER_DIRECTION,
            UPDATE_PLAYER_POSITION,
            START_LISTEN_EVENT,
            STOP_LISTEN_EVENT,
            GET_WINDOW_EVENT,
            PLAYER_SHOOT,
            ENEMY_SHOOT,
            CREATE_PROJECTILE,
            CREATE_MONSTER,
            MOVE_MONSTERS,
            KILL_PROJECTILES,
            CHECK_OFF_SCREEN,
            UPDATE_GAME_STATUS,
            CHECK_COLLISIONS,
            KILL_ENTITY,
            CHECK_LIFES,
            GET_ALL_ROOMS,
            CHECK_LEVEL_FINISHED,
            RENDER_WINDOW,
            START_LEVEL,
            MOVE_BACKGROUND,
            EXECUTE_LEVEL,
            CREATE_PLAYER,
            FAIL_LEVEL,
            WIN_LEVEL,
            MAX_ACTION
        };

        /**
         * @enum SPRITES
         * @brief Defines sprite identifiers for game assets.
         */
        enum SPRITES
        {
            MENU_BACKGROUND,
            GAME_BACKGROUND,
            MY_PLAYER_SHIP,
            SIMPLE_MONSTER,
            ADVANCED_MONSTER,
            PLAYER_SIMPLE_MISSILE,
            MONSTER_SIMPLE_MISSILE,
            OTHER_PLAYER_SHIP,
            LOOSER_SCREEN,
            WIN_SCREEN,
            MONSTER_MULTIPLE_MISSILE,
            LEVEL1,
            LEVEL2
        };

        enum LEVELS
        {
            UN,
            DEUX
        };

        /**
         * @enum FILTER_MODE
         * @brief Defines visual filter modes for accessibility and customization.
         */
        enum FILTER_MODE {
            Neutral,
            Protanopia,
            Deuteranopia,
            Tritanopia,
            Inverted
        };
    }

#endif /* !ENUMS_HPP_ */
