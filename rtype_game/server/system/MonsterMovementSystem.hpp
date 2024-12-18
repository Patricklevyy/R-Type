/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MonsterMovementSystem
*/

#ifndef MONSTERMOVEMENTSYSTEM_HPP_
#define MONSTERMOVEMENTSYSTEM_HPP_
#include "../../../ecs/ECS.hpp"
#include "../../../ecs/Enums_ecs.hpp"
#include "../../../ecs/SparseArray.hpp"
#include "../../../ecs/components/Direction.hpp"
#include "../../../ecs/components/Position.hpp"
#include "../../../ecs/components/Velocity.hpp"
#include "../components/Monster.hpp"
#include "../components/Projectiles.hpp"
#include "../shared/components/Health.hpp"

namespace rtype
{
    class MonsterMovementSystem
    {
    public:
        void moveMonsters(ecs::ECS &ecs, float tps, int window_width, int window_height)
        {
            auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
            auto &directions = std::any_cast<ecs::SparseArray<ecs::Direction> &>(ecs._components_arrays[typeid(ecs::Direction)]);
            auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(ecs._components_arrays[typeid(ecs::Velocity)]);
            auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);

            // for (size_t i = 0; i < monsters.size(); ++i) {
            //     if (positions[i].has_value() && velocities[i].has_value() && directions[i].has_value() && monsters[i].has_value()) {
            //         directions[i].value()._x = ecs::direction::NO_DIRECTION;
            //         directions[i].value()._y = ecs::direction::UP;
            //         positions[i].value()._pos_x -= velocities[i].value().velocity / tps;

            //         if (directions[i].value()._y == ecs::direction::UP) {
            //             directions[i].value()._y = ecs::direction::DOWN;
            //             positions[i].value()._pos_y -= velocities[i].value().velocity / tps;
            //         } else if (directions[i].value()._y == ecs::direction::DOWN) {
            //             directions[i].value()._y = ecs::direction::UP;
            //             positions[i].value()._pos_y += velocities[i].value().velocity / tps;
            //         }
            //     }
            // }
            for (size_t i = 0; i < monsters.size(); ++i) {
                if (positions[i].has_value() && velocities[i].has_value() && directions[i].has_value() && monsters[i].has_value()) {
                    auto &pos = positions[i].value();
                    auto &dir = directions[i].value();
                    auto &vel = velocities[i].value();

                    pos._pos_x -= vel.velocity / tps;

                    if (dir._y == ecs::direction::UP) {
                        pos._pos_y -= vel.velocity / tps;
                        if (pos._pos_y <= 0) {
                            dir._y = ecs::direction::DOWN;
                        }
                    } else if (dir._y == ecs::direction::DOWN) {
                        pos._pos_y += vel.velocity / tps;
                        if (pos._pos_y >= window_height) {
                            dir._y = ecs::direction::UP;
                        }
                    }
                }
            }
        }

    protected:
    private:
    };
}

#endif /* !MONSTERMOVEMENTSYSTEM_HPP_ */
