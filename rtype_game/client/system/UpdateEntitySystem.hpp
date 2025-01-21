/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UpdateEntitySystem
*/

/**
 * @file UpdateEntitySystem.hpp
 * @brief Handles updates to entity properties such as position and health.
 */

#ifndef UPDATEENTITYSYSTEM_HPP_
    #define UPDATEENTITYSYSTEM_HPP_

    #include "../../shared/components/Health.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"

    namespace rtype
    {
        /**
         * @class UpdateEntitySystem
         * @brief Handle entities and their actions.
         */
        class UpdateEntitySystem
        {
            public:
                /**
                * @brief Constructs the UpdateEntitySystem.
                */
                UpdateEntitySystem() {}

                /**
                * @brief Destructor for UpdateEntitySystem.
                */
                ~UpdateEntitySystem() {}

                /**
                 * @brief Updates an entity's properties such as position and health.
                 *
                 * This method modifies the entity's position and health based on the provided parameters.
                 *
                 * @param components_array The ECS component map that contains all components.
                 * @param params A tuple containing the entity's new position (x, y) and health.
                 * @param entity_id The ID of the entity to update.
                 */
                void updateEntity(std::unordered_map<std::type_index, std::any> &components_array, std::pair<size_t, std::pair<float, float>> params, size_t entity_id)
                {
                    auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);

                    if (positions[entity_id].has_value()) {
                        positions[entity_id].value()._pos_x = params.second.first;
                        positions[entity_id].value()._pos_y = params.second.second;
                    }

                }
        };

    }
#endif /* !UPDATEENTITYSYSTEM_HPP_ */
