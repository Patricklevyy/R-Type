/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Structures
*/

#ifndef STRUCTURES_HPP_
    #define STRUCTURES_HPP_

    #include "Includes.hpp"

    struct Message
    {
        unsigned int id : 10; // 10 bits pour 'id' (jusqu'à 1024 id)
        unsigned int action : 6; // 6 bits pour 'action' (jusqu'à 64 types)
        std::string params;
        std::string body;
    };

#endif /* !STRUCTURES_HPP_ */
