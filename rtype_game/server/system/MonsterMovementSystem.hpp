/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MonsterMovementSystem
*/

#ifndef MONSTERMOVEMENTSYSTEM_HPP_
    #define MONSTERMOVEMENTSYSTEM_HPP_
    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/components/Velocity.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../../ecs/Enums_ecs.hpp"
    #include "../shared/components/Health.hpp"
    #include "../components/Projectiles.hpp"
    #include "../components/Monster.hpp"


namespace rtype {
    class MonsterMovementSystem {
        public:
            void moveMonsters(ecs::ECS &ecs, float tps, int window_width, int window_height)
            {
                auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
                auto &directions = std::any_cast<ecs::SparseArray<ecs::Direction> &>(ecs._components_arrays[typeid(ecs::Direction)]);
                auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(ecs._components_arrays[typeid(ecs::Velocity)]);
                auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);

                for (size_t i = 0; i < monsters.size(); ++i) {
                    if (positions[i].has_value() && velocities[i].has_value() && directions[i].has_value() && monsters[i].has_value()) {
                        if (directions[i].value()._x == ecs::direction::LEFT && positions[i].value()._pos_x > (window_width - 100)) {
                            std::cout << "MOVE MONSET " << std::endl;
                            positions[i].value()._pos_x -= velocities[i].value().velocity / tps;
                        }
                    }
                }
            }
        protected:
        private:
    };
}

#endif /* !MONSTERMOVEMENTSYSTEM_HPP_ */
