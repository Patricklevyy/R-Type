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
#include "../RandomNumber.hpp"

namespace rtype
{
    class MonsterMovementSystem
    {
    public:
        void moveMonsters(ecs::ECS &ecs, int window_width, int window_height, RandomNumber randomizer)
        {
            auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
            auto &directions = std::any_cast<ecs::SparseArray<ecs::Direction> &>(ecs._components_arrays[typeid(ecs::Direction)]);
            auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(ecs._components_arrays[typeid(ecs::Velocity)]);
            auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);

            for (size_t i = 0; i < monsters.size(); ++i) {
                if (positions[i].has_value() && velocities[i].has_value() && directions[i].has_value() && monsters[i].has_value()) {
                    if (positions[i].value()._pos_x <= (window_width - 100) && directions[i].value()._x != ecs::direction::NO_DIRECTION) {
                        directions[i].value()._x = ecs::direction::NO_DIRECTION;
                        int random = randomizer.generateRandomNumbers(0, 1);
                        if (random == 0) {
                            directions[i].value()._y = ecs::direction::DOWN;
                        } else {
                            directions[i].value()._y = ecs::direction::UP;
                        }
                    }

                    if (positions[i].value()._pos_y <= 100) {
                        directions[i].value()._y = ecs::direction::DOWN;
                    } else if (positions[i].value()._pos_y >= window_height - 100) {
                        directions[i].value()._y = ecs::direction::UP;
                    }
                }
            }
        }

    protected:
    private:
    };
}

#endif /* !MONSTERMOVEMENTSYSTEM_HPP_ */
