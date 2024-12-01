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
        enum RTYPE_ACTIONS {
            UNDEFINED = -1,
            CREATE_ROOM,
            JOIN_ROOM,
            LEAVE_ROOM,
            EXIT, // FOR DEVELOPMENT ONLY, REMOVE BEFORE DELIVERY
            MAX_ACTION
        };
    }


#endif /* !ENUMS_HPP_ */
