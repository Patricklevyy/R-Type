/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Enums
*/

#ifndef ENUMS_HPP_
    #define ENUMS_HPP_

    namespace rtype
    {
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
            CREATE_PROJECTILE,
            KILL_PROJECTILES,
            CHECK_OFF_SCREEN,
            EXIT, // FOR DEVELOPMENT ONLY, REMOVE BEFORE DELIVERY
            GET_ALL_ROOMS,
            RENDER_WINDOW,
            MAX_ACTION
        };

        enum SPRITES
        {
            BACKGROUND,
            SHIP,
            MONSTER,
            MISSILE
        };
    }

#endif /* !ENUMS_HPP_ */
