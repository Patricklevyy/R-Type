/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GravitySystem
*/

/**
 * @file GravitySystem.hpp
 * @brief Defines the GravitySystem class for handling gravity effects on entities.
 */

#ifndef GRAVITYSYSTEM_HPP_
#define GRAVITYSYSTEM_HPP_

    #include "../../../ecs/Includes_ecs.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Direction.hpp"
    #include "../../../ecs/components/Velocity.hpp"
    #include "../../../ecs/components/Playable.hpp"

    namespace poc_game
    {
        /**
         * @class GravitySystem
         * @brief A system that applies gravity to entities with direction and velocity components.
         */
        class GravitySystem {
            public:
                /**
                 * @brief Executes gravity effects on the provided components.
                 * 
                 * This function applies gravity to entities based on their direction and velocity.
                 * If the entity is moving up, its velocity is divided by a multiplier.
                 * If the entity is moving down, its velocity is multiplied by a different multiplier
                 * and capped at a maximum fall speed. Additionally, if the velocity is below a certain
                 * threshold and the entity is moving up, the direction is flipped to down.
                 * 
                 * @param components_array A map of component arrays indexed by their type.
                 */
                void executeGravity(std::unordered_map<std::type_index, std::any> &components_array) {
                    constexpr float GRAVITY_MULTIPLIER_UP = 2.0f;
                    constexpr float GRAVITY_MULTIPLIER_DOWN = 5.0f;
                    constexpr float MAX_FALL_SPEED = 500.0f;
                    constexpr float FLIP = 10.0f;

                    auto &direction = std::any_cast<ecs::SparseArray<ecs::Direction> &>(components_array[typeid(ecs::Direction)]);
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                    auto &velocity = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array[typeid(ecs::Velocity)]);

                    for (size_t i = 0; i < playables.size(); ++i) {
                        if (playables[i].has_value() &&
                            (i < direction.size() && direction[i].has_value()) &&
                            (i < velocity.size() && velocity[i].has_value())) {

                            auto &dir = direction[i].value();
                            auto &vel = velocity[i].value();

                            if (dir._y == ecs::direction::UP) {
                                vel.velocity /= GRAVITY_MULTIPLIER_UP;
                            } else if (dir._y == ecs::direction::DOWN) {
                                vel.velocity *= GRAVITY_MULTIPLIER_DOWN;
                                if (vel.velocity > MAX_FALL_SPEED)
                                    vel.velocity = MAX_FALL_SPEED;
                            }
                            if (vel.velocity < FLIP && dir._y == ecs::direction ::UP)
                                dir._y = ecs::direction::DOWN;
                        }
                    }
                }

            protected:
            private:
        };

    }

#endif /* !GRAVITYSYSTEM_HPP_ */
