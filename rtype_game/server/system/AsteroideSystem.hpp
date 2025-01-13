/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** AsteroideSystem
*/

#ifndef ASTEROIDESYSTEM_HPP_
    #define ASTEROIDESYSTEM_HPP_

    #include "../components/Monster.hpp"
    #include "../RandomNumber.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../shared/Enums.hpp"
    #include "../../shared/Includes.hpp"
    #include "../../shared/GameplayFactory.hpp"

    namespace rtype
    {
        class AsteroideSystem {
            public:
                AsteroideSystem() {}
                ~AsteroideSystem() {}

                std::list<std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>> spwan_asteroide(RandomNumber randomizer, std::shared_ptr<GameplayFactory> gameplayFactory, int window_height, int window_width, bool isPlaying) {
                    std::list<std::tuple<size_t, std::pair<std::pair<float, float>, std::pair<float, float>>, SPRITES>> asteroids;

                    if (gameplayFactory->getDifficulty() == DIFFICULTY::EASY || !isPlaying)
                        return asteroids;

                    static std::chrono::steady_clock::time_point lastSpawnTime = std::chrono::steady_clock::now();
                    static float spawnInterval = gameplayFactory->getAsteroidsSpawnInterval();
                    std::chrono::steady_clock::time_point currentTime = std::chrono::steady_clock::now();
                    std::chrono::duration<float> deltaTime = currentTime - lastSpawnTime;


                    if (deltaTime.count() >= spawnInterval) {
                        lastSpawnTime = currentTime;

                        for (size_t i = 0; i < static_cast<size_t>(gameplayFactory->getAsteroidsNumberOfSpawn()); ++i) {
                            float xPosition = window_width + 100;
                            float yPosition = randomizer.generateRandomNumbers(100, window_height - 100);

                            SPRITES spriteType = SPRITES::ASTEROIDE;
                            asteroids.push_back({i, {{xPosition, yPosition}, {ecs::direction::LEFT, ecs::direction::NO_DIRECTION}}, spriteType});
                        }
                    }
                    return asteroids;
                }

            protected:
            private:
        };
    }

#endif /* !ASTEROIDESYSTEM_HPP_ */
