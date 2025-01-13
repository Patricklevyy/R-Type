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
#include "../components/Damage.hpp"

namespace rtype
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

        void detectCollisions(std::unordered_map<std::type_index, std::any> &components_array)
        {
            auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);
            auto &damages = std::any_cast<ecs::SparseArray<Damage> &>(components_array[typeid(Damage)]);
            auto &hitboxes = std::any_cast<ecs::SparseArray<Hitbox> &>(components_array[typeid(Hitbox)]);
            auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);
            auto &allies = std::any_cast<ecs::SparseArray<Allies> &>(components_array[typeid(Allies)]);
            auto &ennemies = std::any_cast<ecs::SparseArray<Ennemies> &>(components_array[typeid(Ennemies)]);

            for (std::size_t i = 0; i < positions.size(); ++i) {
                if (positions[i].has_value() && hitboxes[i].has_value()) {
                    for (std::size_t j = i + 1; j < positions.size(); ++j) {
                        if (positions[j].has_value() && hitboxes[j].has_value()) {
                            if (isColliding(positions[i].value(), hitboxes[i].value(), positions[j].value(), hitboxes[j].value())) {
                                bool isAllies = i < allies.size() && j < allies.size() && allies[i].has_value() && allies[j].has_value();
                                bool isEnemies = i < ennemies.size() && j < ennemies.size() && ennemies[i].has_value() && ennemies[j].has_value();
                                if (isAllies || isEnemies) {
                                    continue;
                                }
                                if (i < healths.size() && j < healths.size() && healths[i].has_value() && healths[j].has_value() && i < damages.size() && damages[i].has_value() && j < damages.size() && damages[j].has_value()) {
                                    healths[i].value()._health -= damages[j].value()._damages;
                                    healths[j].value()._health -= damages[i].value()._damages;
                                }
                            }
                        }
                    }
                }
            }
        }

        std::list<std::pair<size_t, BONUS>> detectCollisionsBonus(std::unordered_map<std::type_index, std::any> &components_array) {
            std::cout << "Début de detectCollisionsBonus" << std::endl;

            auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array[typeid(ecs::Position)]);
            auto &hitboxes = std::any_cast<ecs::SparseArray<Hitbox> &>(components_array[typeid(Hitbox)]);
            auto &bonus = std::any_cast<ecs::SparseArray<Bonus> &>(components_array[typeid(Bonus)]);
            auto &playable = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

            std::cout << "Composants récupérés :\n";
            std::cout << "- Positions size: " << positions.size() << "\n";
            std::cout << "- Hitboxes size: " << hitboxes.size() << "\n";
            std::cout << "- Bonus size: " << bonus.size() << "\n";
            std::cout << "- Playable size: " << playable.size() << "\n";

            std::list<std::pair<size_t, BONUS>> dead_bonus;

            for (std::size_t i = 0; i < bonus.size(); ++i) {
                std::cout << "Vérification du bonus " << i << std::endl;
                if (!bonus[i].has_value()) {
                    std::cout << "  -> Bonus " << i << " n'existe pas, continue." << std::endl;
                    continue;
                }
                if (!positions[i].has_value()) {
                    std::cout << "  -> Position pour Bonus " << i << " inexistante, continue." << std::endl;
                    continue;
                }
                if (!hitboxes[i].has_value()) {
                    std::cout << "  -> Hitbox pour Bonus " << i << " inexistante, continue." << std::endl;
                    continue;
                }

                for (std::size_t j = 0; j < playable.size(); ++j) {
                    std::cout << "  Vérification contre Playable " << j << std::endl;
                    if (!playable[j].has_value()) {
                        std::cout << "    -> Playable " << j << " n'existe pas, continue." << std::endl;
                        continue;
                    }
                    if (!positions[j].has_value()) {
                        std::cout << "    -> Position pour Playable " << j << " inexistante, continue." << std::endl;
                        continue;
                    }
                    if (!hitboxes[j].has_value()) {
                        std::cout << "    -> Hitbox pour Playable " << j << " inexistante, continue." << std::endl;
                        continue;
                    }

                    std::cout << "    -> Vérification de collision entre Bonus " << i << " et Playable " << j << std::endl;
                    if (isColliding(positions[i].value(), hitboxes[i].value(), positions[j].value(), hitboxes[j].value())) {
                        std::cout << "      -> COLLISION DETECTED: Bonus " << i << " -> Playable " << j << std::endl;
                        dead_bonus.push_back(std::make_pair(i, bonus[i].value()._type));
                        break; // Bonus collecté, passer au suivant
                    } else {
                        std::cout << "      -> Pas de collision entre Bonus " << i << " et Playable " << j << std::endl;
                    }
                }
            }

            std::cout << "Fin de detectCollisionsBonus, " << dead_bonus.size() << " bonus détectés comme collectés." << std::endl;
            return dead_bonus;
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
        bool isColliding(const ecs::Position &pos1, const rtype::Hitbox &box1, const ecs::Position &pos2, const rtype::Hitbox &box2)
        {
            return (pos1._pos_x < pos2._pos_x + box2._width &&
                    pos1._pos_x + box1._width > pos2._pos_x &&
                    pos1._pos_y < pos2._pos_y + box2._height &&
                    pos1._pos_y + box1._height > pos2._pos_y);
        }
    };
}

#endif /* !COLLISIONSYSTEM_HPP_ */