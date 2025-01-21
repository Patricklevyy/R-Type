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
        /**
         * @class AsteroidSystem
         * @brief A class that handles Asteroid in the game.
         */
        class AsteroideSystem {
            public:

                /**
                * @brief Constructor for the AsteroideSystem class.
                */
                AsteroideSystem() {}

                /**
                * @brief Destructor for the AsteroideSystem class.
                */
                ~AsteroideSystem() {}

                /**
                 * @brief Handles the spawning of asteroids in the game.
                 * @param randomizer An instance of RandomNumber used to generate random vertical positions for the asteroids.
                 * @param gameplayFactory A shared pointer to the GameplayFactory, which provides game settings such as difficulty 
                 *        and asteroid spawn parameters.
                 * @param window_height The height of the game window in pixels.
                 * @param window_width The width of the game window in pixels.
                 * @param isPlaying A boolean indicating whether the game is currently in a playing state.
                 * @return A list of tuples, where each tuple contains:
                 * - A size_t index representing the asteroid ID.
                 * - A pair of pairs representing:
                 *   - The position of the asteroid.
                 *   - The movement direction of the asteroid.
                 * - SPRITES enum indicating the type of sprite.
                 */
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
