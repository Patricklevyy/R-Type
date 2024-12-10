/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_
#include "../Enums_ecs.hpp"
#include "../Includes_ecs.hpp"
#include "../SparseArray.hpp"
#include "../components/Entity.hpp"
#include "../../rtype_game/shared/components/Health.hpp"
#include "../../rtype_game/shared/components/Hitbox.hpp"
#include "../components/Position.hpp"

namespace ecs
{
    class CollisionSystem {

    public:
        void detectCollisions(std::unordered_map<std::type_index, std::any> &components_array)
        {
            auto &positions = std::any_cast<SparseArray<Position> &>(components_array[typeid(Position)]);
            auto &hitboxes = std::any_cast<SparseArray<rtype::Hitbox> &>(components_array[typeid(rtype::Hitbox)]);
            auto &healths = std::any_cast<SparseArray<rtype::Health> &>(components_array[typeid(rtype::Health)]);

            for (std::size_t i = 0; i < positions.size(); ++i) {
                if (positions[i].has_value() && hitboxes[i].has_value()) {
                    for (std::size_t j = i + 1; j < positions.size(); ++j) {
                        if (positions[j].has_value() && hitboxes[j].has_value()) {
                            if (isColliding(positions[i].value(), hitboxes[i].value(), positions[j].value(), hitboxes[j].value())) {
                                std::cout << "Collision detected between Entity " << i << " and Entity " << j << std::endl;
                                if (healths[i].has_value() && healths[j].has_value()) {
                                    healths[i].value()._health -= 20;
                                    healths[j].value()._health -= 20;
                                    std::cout << "Entity " << i << " health reduced to " << healths[i].value()._health << std::endl;
                                    std::cout << "Entity " << j << " health reduced to " << healths[j].value()._health << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }

    protected:
    private:
        bool isColliding(const Position &pos1, const rtype::Hitbox &box1, const Position &pos2, const rtype::Hitbox &box2)
        {
            return !(pos1._pos_x + box1.width < pos2._pos_x ||
            pos1._pos_x > pos2._pos_x + box2.width ||
            pos1._pos_y + box1.height < pos2._pos_y ||
            pos1._pos_x > pos2._pos_y + box2.height);
        }
    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */