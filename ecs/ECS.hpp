/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ECS
*/

#ifndef ECS_HPP_
    #define ECS_HPP_

    #include "Includes_ecs.hpp"
    #include "components/Entity.hpp"
    #include "components/Position.hpp"
    #include "components/Velocity.hpp"
    #include "components/Direction.hpp"
    #include "components/Playable.hpp"
    #include "SparseArray.hpp"

    namespace ecs
    {
        class ECS {
            public:
                ECS() {}
                ~ECS() {}

                void init_basic_registry()
                {
                    addRegistry<Position>();
                    addRegistry<Velocity>();
                    addRegistry<Direction>();
                    addRegistry<Playable>();
                }

                template <typename Component>
                void addRegistry()
                {
                    auto type = std::type_index(typeid(Component));
                    if (_components_arrays.find(type) != _components_arrays.end()) {
                        throw ERROR::ComponentTypeAlreadyExistException();
                    }
                    _components_arrays[type] = SparseArray<Component>();
                    std::cout << "Component registered: " << typeid(Component).name() << std::endl;
                }

                template <typename Component>
                void addComponents(size_t index, const Component& component)
                {
                    auto type = std::type_index(typeid(Component));
                    if (_components_arrays.find(type) == _components_arrays.end()) {
                        throw ERROR::ComponentNotFoundExceptions();
                    }
                    auto& sparse_array = std::any_cast<SparseArray<Component>&>(_components_arrays[type]);

                    if (index >= sparse_array.size()) {
                        sparse_array.resize(index + 1);
                    }
                    sparse_array[index] = component;
                }

                template <typename Component>
                void killEntity(size_t index)
                {
                    for (const auto& [type, anyValue] : _components_arrays) {
                        auto& sparseArray = std::any_cast<SparseArray<Component>>(anyValue);
                        if (index >= sparseArray.size()) {
                            throw ERROR::IdOutOfRangeExceptions();
                        }
                        if (sparseArray[index].has_value()) {
                            sparseArray[index].reset();
                        }
                    }
                }

                void displayPlayableEntityComponents() {
                    auto& positions = std::any_cast<SparseArray<Position>&>(_components_arrays[typeid(Position)]);
                    auto& velocities = std::any_cast<SparseArray<Velocity>&>(_components_arrays[typeid(Velocity)]);
                    auto& directions = std::any_cast<SparseArray<Direction>&>(_components_arrays[typeid(Direction)]);
                    auto& playables = std::any_cast<SparseArray<Playable>&>(_components_arrays[typeid(Playable)]);

                    std::size_t maxEntities = std::max(
                        positions.size(),
                        std::max(velocities.size(), std::max(directions.size(), playables.size()))
                    );
                    for (std::size_t i = 0; i < maxEntities; ++i) {
                        if (i < playables.size() && playables[i].has_value()) {
                            std::cout << "Entity " << i << " (Playable):" << std::endl;

                            if (i < positions.size() && positions[i].has_value()) {
                                const auto& pos = positions[i].value();
                                std::cout << "  Position: (" << pos.pos_x << ", " << pos.pos_y << ")" << std::endl;
                            } else {
                                std::cout << "  Position: None" << std::endl;
                            }

                            if (i < velocities.size() && velocities[i].has_value()) {
                                const auto& vel = velocities[i].value();
                                std::cout << "  Velocity: (" << vel.velocity << ")" << std::endl;
                            } else {
                                std::cout << "  Velocity: None" << std::endl;
                            }

                            if (i < directions.size() && directions[i].has_value()) {
                                const auto& dir = directions[i].value();
                                std::cout << "  Direction: (" << dir._x << ", " << dir._y << ")" << std::endl;
                            } else {
                                std::cout << "  Direction: None" << std::endl;
                            }
                        }
                    }
            }


                std::unordered_map<std::type_index, std::any> _components_arrays;
            protected:
            private:
                std::list<Entity> _dead_entities;


                // std::vector<freset_type> _freset_entity_components;
                // std::vector<freset_all_types> _freset_all_entity_components; ECS ARTHUR, JE SAIS PAS SI C'EST UTILE POUR NOUS
                // std::unordered_map<std::type_index, event_types> _events;
                // std::list<callback_type> _callback_pool;

        };
    }

#endif /* !ECS_HPP_ */
