/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** LevelSystem
*/

/**
 * @file LevelSystem.hpp
 * @brief Manages the levels in the game.
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
    #include "../../shared/GameplayFactory.hpp"

    namespace rtype
    {
        /**
         * @class LevelSystem
         *  This class is used to manage the levels in the game.
         */ 
        class LevelSystem {
            public:

                /**
                 * @brief Default constructor.
                 */
                LevelSystem() {}

                /**
                 * @brief Destructor.
                 */
                ~LevelSystem() {}

                /**
                 * @brief Spawns the boss monster.
                 * 
                 * @param ecs The ECS object containing all entities and components.
                 * @param randomizer Random number generator.
                 * @param gameplayFactory Game configuration.
                 * 
                 * @return List of spawned boss monsters.
                 */
                std::list<SPRITES> spwanBoss(ecs::ECS &ecs, RandomNumber randomizer, std::shared_ptr<GameplayFactory> gameplayFactory)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(ecs._components_arrays.at(typeid(Levels)));

                    std::list<SPRITES> monsters;

                    int monster;
                    std::pair<int, int> monsterToSpwan;

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value() && !levels[i].value().bossSpawned && levels[i].value()._level == LEVELS::BOSS &&
                            levels[i].value()._score >= 20) {

                            levels[i].value().bossSpawned = true;
                            monsterToSpwan = gameplayFactory->getBossLevelSpawn();
                            monster = randomizer.generateRandomNumbers(monsterToSpwan.first, monsterToSpwan.second);

                            monsters.push_back(static_cast<SPRITES>(monster));

                            levels[i].value()._spawnInterval = randomizer.generateRandomNumbers(2.0f, 4.0f);
                        }
                    }
                    return monsters;
                }

                /**
                 * @brief Executes the current level.
                 * 
                 * @param ecs The ECS object containing all entities and components.
                 * @param randomizer Random number generator.
                 * @param gameplayFactory Game configuration.
                 * 
                 * @return List of spawned monsters.
                 */
                std::list<SPRITES> executeLevel(ecs::ECS &ecs, RandomNumber randomizer, std::shared_ptr<GameplayFactory> gameplayFactory)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(ecs._components_arrays.at(typeid(Levels)));

                    std::list<SPRITES> monsters;

                    static std::chrono::steady_clock::time_point lastSpawnTime = std::chrono::steady_clock::now();
                    static float spawnInterval = randomizer.generateRandomNumbers(2.0f, 4.0f);
                    static float accumulatedTime = 0.0f;

                    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
                    std::chrono::duration<float> deltaTime = currentTime - lastSpawnTime;
                    accumulatedTime += deltaTime.count();

                    int monster;
                    std::pair<int, int> monsterToSpwan;

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value() && (accumulatedTime >= spawnInterval) && !levels[i].value().bossSpawned) {
                            auto currentTime = std::chrono::steady_clock::now();
                            std::chrono::duration<float> elapsedTime = currentTime - levels[i].value()._lastSpawnTime;
                            if (elapsedTime.count() >= levels[i].value()._spawnInterval) {
                                monsterToSpwan = gameplayFactory->getMonsterLevelSpawn(levels[i].value()._level);
                                monster = randomizer.generateRandomNumbers(monsterToSpwan.first, monsterToSpwan.second);

                                monsters.push_back(static_cast<SPRITES>(monster));

                                levels[i].value()._lastSpawnTime = currentTime;
                                levels[i].value()._spawnInterval = randomizer.generateRandomNumbers(2.0f, 4.0f);
                            }
                        }
                    }
                    return monsters;
                }

                /**
                 * @brief Gets the current score.
                 * 
                 * @param components_array The ECS component map that contains all components.
                 * 
                 * @return The current score.
                 */
                unsigned int getScore(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(components_array[typeid(Levels)]);

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value()) {
                            return levels[i].value()._score;
                        }
                    }
                    return 0;
                }

                /**
                 * @brief Adds a score to the current score.
                 * 
                 * @param components_array The ECS component map that contains all components.
                 * @param score The score to add.
                 */
                void addToScore(std::unordered_map<std::type_index, std::any> &components_array, unsigned int score)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(components_array[typeid(Levels)]);

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value()) {
                            levels[i].value()._score += score;
                        }
                    }
                }

                /**
                 * @brief Checks if the current level is finished.
                 * 
                 * @param components_array The ECS component map that contains all components.
                 * 
                 * @return A pair containing the current level and a boolean indicating if the level is finished.
                 */
                std::pair<LEVELS, bool> isLevelFinished(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(components_array[typeid(Levels)]);

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value()) {
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

#endif /* !LEVELSYSTEM_HPP_ */
