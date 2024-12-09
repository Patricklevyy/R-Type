/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** CollisionSystem
*/

#ifndef COLLISIONSYSTEM_HPP_
#define COLLISIONSYSTEM_HPP_
#include "../Includes_ecs.hpp"
#include "../Enums_ecs.hpp"
#include "../components/Entity.hpp"
#include "../components/Position.hpp"
#include "../components/Hitbox.hpp"
#include "../SparseArray.hpp"

namespace ecs {
    class CollisionSystem {
        public:
            // CollisionSystem();
            // ~CollisionSystem();
            void detectCollisions(std::unordered_map<std::type_index, std::any>& components_array) {
                auto& positions = std::any_cast<SparseArray<Position>&>(components_array[typeid(Position)]);
                auto& hitboxes = std::any_cast<SparseArray<Hitbox>&>(components_array[typeid(Hitbox)]);

                static_assert(std::is_same_v<decltype(positions.size()), std::size_t>, "positions.size() is not std::size_t");

                for (std::size_t i = 0; i < positions.size(); ++i) {
                    if (positions[i].has_value() && hitboxes[i].has_value()) {
                        for (std::size_t j = i + 1; j < positions.size(); ++j) {
                            if (positions[j].has_value() && hitboxes[j].has_value()) {
                                if (isColliding(positions[i].value(), hitboxes[i].value(), positions[j].value(), hitboxes[j].value())) {
                                    // Définir que faire en cas de collision
                                    std::cout << "Collision detected between Entity " << i << " and Entity " << j << std::endl;
                                }
                            }
                        }
                    }
                }
            }

        protected:
        private:
            bool isColliding(const Position& pos1, const Hitbox& box1, const Position& pos2, const Hitbox& box2) {
                return !(pos1.pos_x + box1.width < pos2.pos_x ||  // Hitbox 1 est à gauche de Hitbox 2
                         pos1.pos_x > pos2.pos_x + box2.width || // Hitbox 1 est à droite de Hitbox 2
                         pos1.pos_y + box1.height < pos2.pos_y || // Hitbox 1 est au-dessus de Hitbox 2
                         pos1.pos_y > pos2.pos_y + box2.height);  // Hitbox 1 est en-dessous de Hitbox 2
            }
    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */