/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem
*/

/**
 * @file CollisionSystem.hpp
 * @brief Handles collision detection between entities in the ECS framework.
 */

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_
#include "../../../ecs/Enums_ecs.hpp"
#include "../../../ecs/Includes_ecs.hpp"
#include "../../../ecs/SparseArray.hpp"
#include "../../../ecs/components/Position.hpp"
#include "../../shared/components/Health.hpp"
#include "../components/Allies.hpp"
#include "../components/Ennemies.hpp"
#include "../components/Hitbox.hpp"

namespace poc_game
{
    /**
     * @class CollisionSystem
     * @brief Detects and processes collisions between entities.
     */
    class CollisionSystem
    {

    public:
        /**
         * @brief Detects collisions between entities and processes health reductions.
         * @param components_array A map containing all component arrays.
         */

        bool detectCollisions(std::unordered_map<std::type_index, std::any> &components_array) {
            auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);
            auto &hitboxes = std::any_cast<ecs::SparseArray<Hitbox> &>(components_array[typeid(Hitbox)]);
            auto &allies = std::any_cast<ecs::SparseArray<Allies> &>(components_array[typeid(Allies)]);
            auto &ennemies = std::any_cast<ecs::SparseArray<Ennemies> &>(components_array[typeid(Ennemies)]);

            for (std::size_t i = 0; i < positions.size(); ++i) {
                if (positions[i].has_value() && hitboxes[i].has_value()) {
                    for (std::size_t j = i + 1; j < positions.size(); ++j) {
                        if (positions[j].has_value() && hitboxes[j].has_value()) {
                            if (isColliding(positions[i].value(), hitboxes[i].value(), positions[j].value(), hitboxes[j].value())) {
                                bool isAllies = i < allies.size() && j < allies.size() && allies[i].has_value() && allies[j].has_value();
                                bool isEnemies = i < ennemies.size() && j < ennemies.size() && ennemies[i].has_value() && ennemies[j].has_value();

                                // Ignore collisions between entities of the same type
                                if (isAllies || isEnemies) {
                                    continue;
                                }

                                // Collision detected
                                std::cout << "Collision detected between Entity " << i << " and Entity " << j << std::endl;
                                return true;
                            }
                        }
                    }
                }
            }
            // No collision detected
            return false;
        }


    protected:
    private:
        /**
         * @brief Checks if two entities are colliding based on their positions and hitboxes.
         * @param pos1 Position of the first entity.
         * @param box1 Hitbox of the first
         * @param pos1 Position of the first entity.
         * @param box1 Hitbox of the first entity.
         * @param pos2 Position of the second entity.
         * @param box2 Hitbox of the second entity.
         * @return True if the entities are colliding, false otherwise.
         */
        bool isColliding(const ecs::Position &pos1, const Hitbox &box1, const ecs::Position &pos2, const Hitbox &box2)
        {
            return (pos1._pos_x < pos2._pos_x + box2._width &&
                    pos1._pos_x + box1._width > pos2._pos_x &&
                    pos1._pos_y < pos2._pos_y + box2._height &&
                    pos1._pos_y + box1._height > pos2._pos_y);
        }
    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */