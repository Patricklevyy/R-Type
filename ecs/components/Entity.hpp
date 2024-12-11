/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Entity
*/

/**
 * @file Entity.hpp
 * @brief Defines the Entity class for the ECS framework.
 */

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

    namespace ecs
    {
        /**
         * @class Entity
         * @brief Represents a unique entity in the ECS framework.
         */
        class Entity
        {
        public:
            /**
             * @brief Constructs an Entity with a specific index.
             * @param index Unique identifier for the entity.
             */
            Entity(size_t index) : _index(index) {}

            /**
             * @brief Destructor for Entity.
             */
            ~Entity() {}

            /**
             * @brief The unique index of the entity.
             */
            size_t _index;

        protected:
        private:
        };
    }

#endif /* !ENTITY_HPP_ */
