/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Entity
*/

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_
    namespace ecs
    {
        class Entity
        {
        public:
            Entity(size_t index) : _index(index) {}
            ~Entity() {}

            size_t _index;

        protected:
        private:
        };
    }

#endif /* !ENTITY_HPP_ */
