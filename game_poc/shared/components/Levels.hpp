/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Levels
*/

#ifndef LEVELS_HPP_
    #define LEVELS_HPP_

    #include "../../shared/Enums.hpp"

    namespace poc_game
    {
    /**
     * @class Levels
     * @brief A class that handles levels of the game.
     */
        class Levels
        {
            public:
                /**
                 * @brief Constructor for the Health class.
                 */
                Levels(LEVELS level) : _level(level), _spawnInterval(2.0f) {
                    _lastSpawnTime = std::chrono::steady_clock::now();
                }

                unsigned int _score = 0;
                LEVELS _level;
                float _spawnInterval;
                std::chrono::steady_clock::time_point _lastSpawnTime;
            };
    }
#endif /* !LEVELS_HPP_ */

