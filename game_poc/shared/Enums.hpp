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

    namespace poc_game
    {

        /**
         * @enum RTYPE_ACTIONS
         * @brief Defines all the possible actions in the R-Type game.
         */
        enum POC_GAME_ACTIONS
        {
            UNDEFINED = -1,
            START,
            PLAY,
            JUMP,
            RESTART,
            EXECUTE_GRAVITY,
            SPAWN_PIPE,
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
            CHECK_EVENT_WINDOW,
            CREATE_CLIENT,
            CREATE_TEAMMATE,
            UPDATE_POSITIONS,
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
            UPDATE_POSITIONS_FROM_SERVER,
            REMOVE_ATH,
            MAX_ACTION
        };

        /**
         * @enum SPRITES
         * @brief Defines sprite identifiers for game assets.
         */
        enum SPRITES
        {
            BACKGROUND,
            PLAYER,
            PIPE_DOWN,
            PIPE_UP,
            PLAY_BUTTON,
            REPLAY_BUTTON
        };

        enum LEVELS
        {
            UN,
            DEUX,
            BOSS
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
