/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LevelSystem
*/

#ifndef LEVELSYSTEM_HPP_
    #define LEVELSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/Enums_ecs.hpp"
    #include "../../../ecs/Includes_ecs.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../components/Allies.hpp"
    #include "../components/Ennemies.hpp"
    #include "../components/Hitbox.hpp"
    #include "../../shared/components/Levels.hpp"
    #include "../RandomNumber.hpp"

    namespace rtype
    {
        class LevelSystem {
            public:
                LevelSystem() {}
                ~LevelSystem() {}

                std::list<SPRITES> executeLevel(ecs::ECS &ecs, RandomNumber randomizer)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(ecs._components_arrays.at(typeid(Levels)));

                    std::list<SPRITES> monsters;

                    static std::chrono::steady_clock::time_point lastSpawnTime = std::chrono::steady_clock::now();
                    static float spawnInterval = randomizer.generateRandomNumbers(2.0f, 4.0f);
                    static float accumulatedTime = 0.0f;

                    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
                    std::chrono::duration<float> deltaTime = currentTime - lastSpawnTime;
                    accumulatedTime += deltaTime.count();

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value() && (accumulatedTime >= spawnInterval)) {
                            auto currentTime = std::chrono::steady_clock::now();
                            std::chrono::duration<float> elapsedTime = currentTime - levels[i].value()._lastSpawnTime;
                            switch (levels[i].value()._level)
                            {
                            case LEVELS::UN:
                                if (elapsedTime.count() >= levels[i].value()._spawnInterval) {

                                    monsters.push_back(SPRITES::SIMPLE_MONSTER);

                                    levels[i].value()._lastSpawnTime = currentTime;
                                    levels[i].value()._spawnInterval = randomizer.generateRandomNumbers(2.0f, 4.0f);
                                }
                                break;
                            case LEVELS::DEUX:
                                if (elapsedTime.count() >= levels[i].value()._spawnInterval) {

                                    monsters.push_back(SPRITES::ADVANCED_MONSTER);

                                    levels[i].value()._lastSpawnTime = currentTime;
                                    levels[i].value()._spawnInterval = randomizer.generateRandomNumbers(1.5f, 4.0f);
                                }
                                break;
                            default:
                                break;
                            }
                        }
                    }
                    return monsters;
                }

            protected:
            private:
        };
    }

#endif /* !LEVELSYSTEM_HPP_ */
