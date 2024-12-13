/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UpdateEntitySystem
*/

#ifndef UPDATEENTITYSYSTEM_HPP_
    #define UPDATEENTITYSYSTEM_HPP_

    #include "../../shared/components/Health.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"

    namespace rtype
    {
        class UpdateEntitySystem
        {
            public:
                UpdateEntitySystem() {}
                ~UpdateEntitySystem() {}

                void updateEntity(std::unordered_map<std::type_index, std::any> &components_array, std::tuple<size_t, std::pair<float, float>, int> params)
                {
                    auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);

                    // size_t entity_id = std::get<0>(params);

                    // if (positions[entity_id].has_value() && healths[entity_id].has_value()) {
                    //     positions[entity_id].value()._pos_x = std::get<1>(params).first;
                    //     positions[entity_id].value()._pos_y = std::get<1>(params).second;
                    //     healths[entity_id].value()._health = std::get<2>(params);
                    // }

                }
        };

    }
#endif /* !UPDATEENTITYSYSTEM_HPP_ */
