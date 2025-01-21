/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AnimationSystem
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
       * @brief Handle the animation in game.
       */
        class AnimationSystem {
            public:
                /**
                 * @brief Constructor for the AnimationSystem class.
                 */
                AnimationSystem() {}

                /**
                 * @brief Destructor for the AnimationSystem class.
                 */
                ~AnimationSystem() {}

                /**
                 * @brief Checks if there is at least one active animation in the component array.
                 * @param components_array Reference to an unordered map containing components indexed by type.
                 * @return true if at least one Animation component exists and is active.
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
                 * @brief Retrieves the index of the first active animation in the component array.
                 * @param components_array Reference to an unordered map containing components indexed by type.
                 * @return The index of the first active Animation component. Returns 0 if no active animations are found.
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
                 * @brief Updates the position of active animations in the component array.
                 * @param components_array A reference to an unordered map containing components indexed by type.
                 * @param player_positions A pair of floats representing the player's position.
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
