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
            EXIT, // FOR DEVELOPMENT ONLY, REMOVE BEFORE DELIVERY
            MAX_ACTION
        };
    }

#endif /* !ENUMS_HPP_ */
