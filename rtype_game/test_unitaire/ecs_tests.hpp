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

    /**
     * @brief Test behavior when attempting to add a registry that already exists.
     */
    void add_registry_already_exist()
    {
        ecs::ECS ecs;

        ecs.addRegistry<ecs::Position>();
        ecs.addRegistry<ecs::Position>();
    }

    /**
     * @brief Test behavior when adding a component to an entity in a registry that does not exist.
     */
    void add_component_dont_exist()
    {
        ecs::ECS ecs;

        ecs.addComponents<ecs::Position>(0, ecs::Position());
    }

#endif /* !ECS_TESTS_HPP_ */
