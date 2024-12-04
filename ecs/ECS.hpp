/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ECS
*/

#ifndef ECS_HPP_
    #define ECS_HPP_

    #include "Includes.hpp"
    #include "components/Entity.hpp"
    #include "SparseArray.hpp"

    namespace ecs
    {
        class ECS {
            public:
                ECS() {}
                ~ECS() {}

                template <typename Component>
                void addRegistry()
                {
                    auto type = std::type_index(typeid(Component));
                    if (_components_arrays.find(type) != _components_arrays.end()) {
                        throw ERROR::ComponentTypeAlreadyExistException();
                    }
                    _components_arrays[type] = SparseArray<std::optional<Component>>();
                    std::cout << "Component registered: " << typeid(Component).name() << std::endl;
                }

                template <typename Component>
                void addComponents(size_t index, const Component& component)
                {
                    auto type = std::type_index(typeid(Component));
                    if (_components_arrays.find(type) == _components_arrays.end()) {
                        throw ERROR::ComponentNotFoundExceptions();
                    }
                    auto& sparse_array = std::any_cast<SparseArray<std::optional<Component>>&>(_components_arrays[type]);

                    if (index >= sparse_array.size()) {
                        sparse_array.resize(index + 1);
                    }
                    sparse_array[index] = component;
                }

            protected:
            private:
                unsigned int _nb_entities = 0;
                std::unordered_map<std::type_index, std::any> _components_arrays;
                std::list<Entity> _dead_entities;


                // std::vector<freset_type> _freset_entity_components;
                // std::vector<freset_all_types> _freset_all_entity_components; ECS ARTHUR, JE SAIS PAS SI C'EST UTILE POUR NOUS
                // std::unordered_map<std::type_index, event_types> _events;
                // std::list<callback_type> _callback_pool;

        };
    }

#endif /* !ECS_HPP_ */
