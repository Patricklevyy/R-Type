/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Structures_ecs
*/

#ifndef STRUCTURES_ECS_HPP_
    #define STRUCTURES_ECS_HPP_

    #include "Includes_ecs.hpp"

    namespace ecs
    {
        namespace udp
        {
            struct Message
            {
                unsigned int id : 10;    /* 10 bits pour 'id' (jusqu'à 1024 id) */
                unsigned int action : 6; /* 6 bits pour 'action' (jusqu'à 64 types) */
                std::string params;
                std::string secret_key; /* Clé secrète pour l'authentification */
            };
        }
    }

#endif /* !STRUCTURES_ECS_HPP_ */
