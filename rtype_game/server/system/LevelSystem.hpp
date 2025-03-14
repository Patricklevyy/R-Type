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
    #include "../../shared/GameplayFactory.hpp"

    namespace rtype
    {
        /**
        * @class LevelSystem
        * @brief Manages Levels in the game.
        */
        class LevelSystem {
            public:
                /**
                * @brief Constructor for the LevelSystem class.
                */
                LevelSystem() {}

                /**
                * @brief Destructor for the LevelSystem class.
                */
                ~LevelSystem() {}

                /**
                 * @brief Handle the spawn of the Boss Monster.
                 * @param ecs The Entity Components System that contains all the entity in the game and caontains also informations such as health
                 * @param randomizer An instance of RandomNumber used to generate random vertical positions for the Boss.
                 * @param gameplayFactory A shared pointer to the GameplayFactory, which provides game settings such as 
                 *        Boss spawn parameters.
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
                 * @brief Handle the level started by the player.
                 * @param ecs The Entity Components System that contains all the entity in the game and caontains also informations such as health.
                 * @param randomizer An instance of RandomNumber used to generate random vertical positions for the Monsters.
                 * @param gameplayFactory A shared pointer to the GameplayFactory, which provides game settings such as 
                 *        Monster spawn parameters.
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
                 * @brief Get the score of the player.
                 * @param components_array An unordered map that conatined all the components, and wich permit to get the score.
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
                 * @brief Increase the score of the player.
                 * @param components_array An unordered map that conatined all the components, and wich permit to get the score.
                 * @param score The score to add to the player.
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
                 * @brief Says the status of the levels (finished or not).
                 * @param components_array An unordered map that conatined all the components, and wich permit to get informations on the game.
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
