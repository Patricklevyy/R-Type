/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** DirectionSystem
*/

#ifndef DIRECTIONSYSTEM_HPP_
    #define DIRECTIONSYSTEM_HPP_

    #include "../../../ecs/Includes_ecs.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../../ecs/components/Playable.hpp"

    namespace rtype
    {
        class DirectionSystem
        {
        public:
            void updatePlayerDirection(std::unordered_map<std::type_index, std::any> &components_array, ecs::direction x, ecs::direction y, size_t index_player)
            {
                auto &direction = std::any_cast<ecs::SparseArray<ecs::Direction> &>(components_array[typeid(ecs::Direction)]);

                if (direction[index_player].has_value()) {
                    if (ecs::direction::NO_CHANGE != x)
                        direction[index_player].value()._x = x;
                    if (ecs::direction::NO_CHANGE != y)
                        direction[index_player].value()._y = y;
                    return;
                }
            }

        protected:
        private:
        };
    }
#endif /* !DIRECTIONSYSTEM_HPP_ */
