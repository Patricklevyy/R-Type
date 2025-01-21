/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GravitySystem
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
         * @brief A class that handles the gravity in game.
         */
        class GravitySystem {
            public:
                /**
                 * @brief Function that execute eath attraction to pull player down.
                 * @param components_array The array of components for the ECS.
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
