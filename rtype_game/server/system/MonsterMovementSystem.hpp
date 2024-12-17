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
    #include "../shared/components/Health.hpp"
    #include "../components/Projectiles.hpp"


namespace ecs {
    class MonsterMovementSystem {
        public:
            void moveMonsters(ECS &ecs, float tps)
            {
                auto &positions = std::any_cast<SparseArray<Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
                auto &directions = std::any_cast<SparseArray<Direction> &>(ecs._components_arrays[typeid(ecs::Direction)]);
                auto &velocities = std::any_cast<SparseArray<Velocity> &>(ecs._components_arrays[typeid(ecs::Velocity)]);

                for (size_t i = 0; i < positions.size(); ++i) {
                    if (positions[i].has_value() && velocities[i].has_value()) {
                        positions[i]->_pos_x += velocities[i]->velocity * tps; // Not sure of what i am doing here
                    }
                }
            }
        protected:
        private:
    };
}

#endif /* !MONSTERMOVEMENTSYSTEM_HPP_ */
