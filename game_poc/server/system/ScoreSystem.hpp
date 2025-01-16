/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScoreSystem
*/

#ifndef SCORESYSTEM_HPP_
    #define SCORESYSTEM_HPP_

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

    namespace poc_game
    {
        class ScoreSystem {
            public:
                ScoreSystem() {}
                ~ScoreSystem() {}

                void addToScore(std::unordered_map<std::type_index, std::any> &components_array, unsigned int score)
                {
                    // auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(components_array[typeid(Levels)]);

                    // for (std::size_t i = 0; i < levels.size(); ++i) {
                    //     if (levels[i].has_value()) {
                    //         levels[i].value()._score += score;
                    //     }
                    // }
                }

            protected:
            private:
        };
    }

#endif /* !SCORESYSTEM_HPP_ */
