/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    #include "../Includes.hpp"

    namespace ecs
    {
        class Entity {
            public:
                Entity();
                ~Entity();

                size_t index;

            protected:
            private:
        };
    }

#endif /* !ENTITY_HPP_ */
