/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MonsterMovementSystem
*/

/**
 * @file MonsterMovementSystem.hpp
 * @brief Handles the movement of monster entities.
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
#include "../../shared/components/Health.hpp"
#include "../RandomNumber.hpp"

namespace rtype
{
    /**
     * @class MonsterMovementSystem
     * @brief Manages the movement logic for monster entities.
     */
    class MonsterMovementSystem
    {
    public:

        /**
         * @brief Updates monster positions based on their velocity and direction.
         * @param ecs The ECS manager.
         * @param window_width Width of the game window.
         * @param window_height Height of the game window.
         * @param randomizer Random number generator for direction changes.
         */
        void moveMonsters(ecs::ECS &ecs, int window_width, int window_height, RandomNumber randomizer)
        {
            auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
            auto &directions = std::any_cast<ecs::SparseArray<ecs::Direction> &>(ecs._components_arrays[typeid(ecs::Direction)]);
            auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(ecs._components_arrays[typeid(ecs::Velocity)]);
            auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);

            for (size_t i = 0; i < monsters.size(); ++i) {
                if (positions[i].has_value() && velocities[i].has_value() && directions[i].has_value() && monsters[i].has_value()) {
                    if (randomizer.generateRandomNumbers(0, 100) < 5) {
                        int randX = randomizer.generateRandomNumbers(0, 2);
                        if (randX == 0) directions[i].value()._x = ecs::direction::LEFT;
                        else if (randX == 1) directions[i].value()._x = ecs::direction::RIGHT;
                        else directions[i].value()._x = ecs::direction::NO_DIRECTION;

                        int randY = randomizer.generateRandomNumbers(0, 2);
                        if (randY == 0) directions[i].value()._y = ecs::direction::UP;
                        else if (randY == 1) directions[i].value()._y = ecs::direction::DOWN;
                        else directions[i].value()._y = ecs::direction::NO_DIRECTION;
                    }

                    if (positions[i].value()._pos_x <= 200) {
                        directions[i].value()._x = ecs::direction::RIGHT;
                    } else if (positions[i].value()._pos_x >= window_width - 200) {
                        directions[i].value()._x = ecs::direction::LEFT;
                    }

                    if (positions[i].value()._pos_y <= 150) {
                        directions[i].value()._y = ecs::direction::DOWN;
                    } else if (positions[i].value()._pos_y >= window_height - 150) {
                        directions[i].value()._y = ecs::direction::UP;
                    }
                }
            }
        }
        // void moveMonsters(ecs::ECS &ecs, int window_width, int window_height, RandomNumber randomizer)
        // {
        //     auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
        //     auto &directions = std::any_cast<ecs::SparseArray<ecs::Direction> &>(ecs._components_arrays[typeid(ecs::Direction)]);
        //     auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(ecs._components_arrays[typeid(ecs::Velocity)]);
        //     auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(ecs._components_arrays[typeid(Monster)]);

        //     for (size_t i = 0; i < monsters.size(); ++i) {
        //         if (positions[i].has_value() && velocities[i].has_value() && directions[i].has_value() && monsters[i].has_value()) {
        //             if (positions[i].value()._pos_x <= (window_width - 150) && directions[i].value()._x != ecs::direction::NO_DIRECTION) {
        //                 directions[i].value()._x = ecs::direction::NO_DIRECTION;
        //                 int random = randomizer.generateRandomNumbers(0, 1);
        //                 if (random == 0) {
        //                     directions[i].value()._y = ecs::direction::DOWN;
        //                 } else {
        //                     directions[i].value()._y = ecs::direction::UP;
        //                 }
        //             }

        //             if (positions[i].value()._pos_y <= 150) {
        //                 directions[i].value()._y = ecs::direction::DOWN;
        //             } else if (positions[i].value()._pos_y >= window_height - 150) {
        //                 directions[i].value()._y = ecs::direction::UP;
        //             }
        //         }
        //     }
        // }

    protected:
    private:
    };
}

#endif /* !MONSTERMOVEMENTSYSTEM_HPP_ */
