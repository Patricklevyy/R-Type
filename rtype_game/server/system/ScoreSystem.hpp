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

    namespace rtype
    {
        class ScoreSystem {
            public:
                ScoreSystem() {}
                ~ScoreSystem() {}

                void addToScore(std::unordered_map<std::type_index, std::any> &components_array, unsigned int score)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(components_array[typeid(Levels)]);

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value()) {
                            levels[i].value()._score += score;
                        }
                    }
                }

                std::pair<LEVELS, bool> isLevelFinished(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(components_array[typeid(Levels)]);

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value()) {
                            std::cout << "SCOREEEE \n\n\n\n" << levels[i].value()._score << std::endl;
                            switch (levels[i].value()._level)
                            {
                            case LEVELS::UN:
                                if (levels[i].value()._score >= 12) {
                                    levels[i].value()._score = 0;
                                    return std::make_pair(levels[i].value()._level, true);
                                } else {
                                    return std::make_pair(levels[i].value()._level, false);
                                }
                            case LEVELS::DEUX:
                                if (levels[i].value()._score >= 20) {
                                    levels[i].value()._score = 0;
                                    return std::make_pair(levels[i].value()._level, true);
                                } else {
                                    return std::make_pair(levels[i].value()._level, false);
                                }
                            case LEVELS::BOSS:
                                if (levels[i].value()._score >= 30) {
                                    levels[i].value()._score = 0;
                                    return std::make_pair(levels[i].value()._level, true);
                                } else {
                                    return std::make_pair(levels[i].value()._level, false);
                                }
                            default:
                                break;
                            }
                        }
                    }
                    return std::make_pair(LEVELS::UN, false);
                }

            protected:
            private:
        };
    }

#endif /* !SCORESYSTEM_HPP_ */
