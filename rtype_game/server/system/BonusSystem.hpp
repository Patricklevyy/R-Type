/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** BonusSystem
*/

#ifndef BONUSSYSTEM_HPP_
#define BONUSSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/components/Playable.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/Enums_ecs.hpp"
    #include "../../../ecs/Includes_ecs.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../components/Allies.hpp"
    #include "../components/Ennemies.hpp"
    #include "../components/Hitbox.hpp"
    #include "../components/Damage.hpp"
    #include "../../shared/components/Health.hpp"

    namespace rtype
    {
        class BonusSystem {
            public:
                BonusSystem() {}
                ~BonusSystem() {}

                void addPlayerLife(std::unordered_map<std::type_index, std::any> &components_array, size_t index, int life) {
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

                    if (index < playables.size() && playables[index].has_value() && index < healths.size() && healths[index].has_value()) {
                        healths[index].value()._health += life;
                    }
                }

                void changePlayerVelocity(std::unordered_map<std::type_index, std::any> &components_array, size_t index, int velocity) {
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                    auto &velocities = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array[typeid(ecs::Velocity)]);

                    if (index < playables.size() && playables[index].has_value() && index < velocities.size() && velocities[index].has_value()) {
                        velocities[index].value().velocity += velocity;
                    }
                }

            protected:
            private:
        };
    }

#endif /* !BONUSSYSTEM_HPP_ */
