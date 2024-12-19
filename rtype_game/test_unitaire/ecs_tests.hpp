/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ecs_tests
*/

#ifndef ECS_TESTS_HPP_
    #define ECS_TESTS_HPP_


    #include "../../ecs/ECS.hpp"
    #include "../../ecs/components/Position.hpp"

    void add_registry_already_exist()
    {
        ecs::ECS ecs;

        ecs.addRegistry<ecs::Position>();
        ecs.addRegistry<ecs::Position>();
    }

    void add_component_dont_exist()
    {
        ecs::ECS ecs;

        ecs.addComponents<ecs::Position>(0, ecs::Position());
    }

    void player_dont_exist()
    {
        ecs::ECS ecs;

        ecs.getIndexPlayer();
    }

#endif /* !ECS_TESTS_HPP_ */
