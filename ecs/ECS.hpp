/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ECS
*/

#ifndef ECS_HPP_
    #define ECS_HPP_

    #include "Includes.hpp"

    namespace ecs
    {
        class ECS {
            public:
                ECS();
                ~ECS();

            protected:
            private:
                std::size_t _nb_entities;
                std::unordered_map<std::type_index, std::any> _components;


                // std::list<Entity> _dead_entities;
                // std::vector<freset_type> _freset_entity_components;
                // std::vector<freset_all_types> _freset_all_entity_components; ECS ARTHUR, JE SAIS PAS SI C'EST UTILE POUR NOUS
                // std::unordered_map<std::type_index, event_types> _events;
                // std::list<callback_type> _callback_pool;

        };
    }

#endif /* !ECS_HPP_ */
