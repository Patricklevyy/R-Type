/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AnimationSystem
*/

/**
 * @file AnimationSystem.hpp
 * @brief Header file for the AnimationSystem class.
 *
 * This file contains the declaration of the AnimationSystem class that is responsible
 * for managing and updating animations in the game. The class interacts with ECS
 * components such as Animation, Position, and Playable to handle animations related
 * to entities in the game.
 */

#ifndef ANIMATIONSYSTEM_HPP_
#define ANIMATIONSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/components/Playable.hpp"
    #include "../../shared/components/Levels.hpp"
    #include "../components/Displayable.hpp"
    #include "../components/Window.hpp"
    #include "../components/Animation.hpp"

    namespace rtype
    {
        /**
         * @class AnimationSystem
         * @brief A class for managing and updating animations for entities in the game.
         *
         * This class works with components from the ECS (Entity-Component-System) to check
         * whether animations are active and to update the corresponding animations and
         * entity positions.
         */
        class AnimationSystem {
            public:
                /**
                 * @brief Default constructor for the AnimationSystem class.
                 */
                AnimationSystem() {}
                /**
                 * @brief Destructor for the AnimationSystem class.
                 */
                ~AnimationSystem() {}

                /**
                 * @brief Check if any entity has an active animation.
                 * 
                 * This method checks the component array for any entity with an active animation.
                 * It returns true if at least one animation exists for an entity.
                 * 
                 * @param components_array The array of components for entities in the ECS system.
                 * @return True if any animation exists, false otherwise.
                 */
                bool isAlreadyAnimation(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &animations = std::any_cast<ecs::SparseArray<Animation> &>(components_array.at(typeid(Animation)));

                    for (std::size_t i = 0; i < animations.size(); ++i) {
                        if (animations[i].has_value()) {
                            return true;
                        }
                    }
                    return false;
                }
                /**
                 * @brief Get the index of the charged animation for an entity.
                 * 
                 * This method retrieves the index of the first entity that has a charged
                 * animation in its components.
                 * 
                 * @param components_array The array of components for entities in the ECS system.
                 * @return The index of the charged animation, or 0 if none is found.
                 */
                size_t getChargedAnimationIndex(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &animations = std::any_cast<ecs::SparseArray<Animation> &>(components_array.at(typeid(Animation)));

                    for (std::size_t i = 0; i < animations.size(); i++) {
                        if (animations[i].has_value()) {
                            return i;
                        }
                    }
                    return 0;
                }
                /**
                 * @brief Update the charged animation's position.
                 * 
                 * This method updates the position of the charged animation based on the 
                 * player's position (coordinates). It updates the position component of the
                 * corresponding entity.
                 * 
                 * @param components_array The array of components for entities in the ECS system.
                 * @param player_positions The player's current position (x, y) to update the animation.
                 */
                void updateChargedAnimation(std::unordered_map<std::type_index, std::any> &components_array, std::pair<float, float> player_positions)
                {
                    auto &animations = std::any_cast<ecs::SparseArray<Animation> &>(components_array.at(typeid(Animation)));
                    auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array.at(typeid(ecs::Position)));

                    for (std::size_t i = 0; i < animations.size(); ++i) {
                        if (animations[i].has_value() && i < positions.size() && positions[i].has_value()) {
                            positions[i].value()._pos_x = player_positions.first;
                            positions[i].value()._pos_y = player_positions.second;
                        }
                    }
                }

            protected:
            private:
        };
    }

#endif /* !ANIMATIONSYSTEM_HPP_ */
