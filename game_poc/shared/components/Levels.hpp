/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Levels
*/

#ifndef LEVELS_HPP_
    #define LEVELS_HPP_

    #include "../../shared/Enums.hpp"

    /**
     * @file Levels.hpp
     * @brief Defines the Levels class for the poc_game namespace.
     */
    namespace poc_game
    {

        /**
         * @class Levels
         * @brief Manages the game levels and related properties.
         */
        class Levels
        {
            public:
                /**
                 * @brief Constructs the Levels object with a specified level.
                 * @param level The level to set.
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

