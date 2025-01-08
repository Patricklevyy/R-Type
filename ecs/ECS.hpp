/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ECS
*/

/**
 * @file ECS.hpp
 * @brief Core of the Entity-Component-System (ECS) architecture for managing entities and components.
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
        /**
         * @class ECS
         * @brief Manages entities and their components in an ECS architecture.
         */
        class ECS
        {
        public:
            ECS() {}
            ~ECS() {}

            /**
             * @brief Initializes basic registries for default components.
             */
            void init_basic_registry()
            {
                addRegistry<Position>();
                addRegistry<Velocity>();
                addRegistry<Direction>();
                addRegistry<Playable>();
            }

            /**
             * @brief Retrieves a component from an entity.
             * @tparam Component The type of component to retrieve.
             * @param index The ID of the entity.
             * @return A reference to the component.
             * @throws ComponentNotFoundExceptions If the component type is not registered.
             */
            template <typename Component>
            Component &getComponent(size_t index)
            {
                auto type = std::type_index(typeid(Component));
                if (_components_arrays.find(type) == _components_arrays.end())
                {
                    throw ERROR::ComponentNotFoundExceptions();
                }
                auto &sparse_array = std::any_cast<SparseArray<Component> &>(_components_arrays.at(type));
                return sparse_array[index].value();
            }

            /**
             * @brief Adds a registry for a specific component type.
             * @tparam Component The type of component to register.
             * @throws ComponentTypeAlreadyExistException If the component type is already registered.
             */
            template <typename Component>
            void addRegistry()
            {
                auto type = std::type_index(typeid(Component));
                if (_components_arrays.find(type) != _components_arrays.end())
                {
                    throw ERROR::ComponentTypeAlreadyExistException();
                }
                _components_arrays[type] = SparseArray<Component>();
                std::cout << "Component registered: " << typeid(Component).name() << std::endl;
            }

            /**
             * @brief Adds a component to an entity.
             * @tparam Component The type of component to add.
             * @param index The ID of the entity.
             * @param component The component to associate with the entity.
             * @throws ComponentNotFoundExceptions If the component type is not registered.
             */
            template <typename Component>
            void addComponents(size_t index, const Component &component)
            {
                auto type = std::type_index(typeid(Component));
                if (_components_arrays.find(type) == _components_arrays.end())
                {
                    throw ERROR::ComponentNotFoundExceptions();
                }
                auto &sparse_array = std::any_cast<SparseArray<Component> &>(_components_arrays[type]);

                if (index >= sparse_array.size())
                {
                    sparse_array.resize(index + 1);
                }
                sparse_array[index] = component;
            }

            /**
             * @brief Removes all components from an entity, marking it as "dead."
             * @tparam Component The component type to process.
             * @param index The ID of the entity.
             * @throws IdOutOfRangeExceptions If the entity ID is out of range.
             */
            template <typename Component>
            void killEntityFromRegistry(std::size_t entityIndex)
            {
                auto type = std::type_index(typeid(Component));
                if (_components_arrays.find(type) != _components_arrays.end()) {
                    auto &sparseArray = std::any_cast<SparseArray<Component>&>(_components_arrays[type]);
                    sparseArray.remove(entityIndex);
                }
            }

            void addDeadEntity(size_t index)
            {
                _dead_entities.push_back(Entity(index));
            }

            /**
             * @brief Allows us the get the list of the dead entities.
             */
            std::pair<bool, size_t> getDeadEntityIndex()
            {
                if (_dead_entities.empty()) {
                    return std::make_pair<bool, size_t>(false, 0);
                } else {
                    std::pair<bool, size_t> entity = std::make_pair(true, _dead_entities.front()._index);
                    _dead_entities.pop_front();
                    return entity;
                }
            }

            std::unordered_map<std::type_index, std::any> _components_arrays; /**< Maps component types to sparse arrays. */

        protected:
        private:

            std::list<Entity> _dead_entities; /**< List of entities marked as "dead." */
        };
    }

#endif /* !ECS_HPP_ */
