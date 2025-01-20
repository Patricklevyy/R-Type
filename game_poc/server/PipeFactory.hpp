/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PipeFactory
*/

#ifndef PIPEFACTORY_HPP_
    #define PIPEFACTORY_HPP_

    #include "RandomNumber.hpp"
    #include "../shared/Enums.hpp"

    namespace poc_game
    {
        
        /**
         * @class PipeFactory
         * @brief A factory class for creating various game objects.
         *
         * The PipeFactory class provides static methods to generate game objects
         * such as monsters with specific spawn coordinates.
         */
        class PipeFactory {
        public:
                /**
                 * @brief Generates spawn coordinates for a monster.
                 *
                 * This static method generates a pair of coordinates for spawning a monster
                 * within the game window. The x-coordinate is set to be slightly outside the
                 * right edge of the window, while the y-coordinate is randomly generated
                 * within a specified range.
                 *
                 * @param window_width The width of the game window.
                 * @param window_height The height of the game window.
                 * @param randomizer An instance of RandomNumber used to generate random numbers.
                 * @return A std::pair<int, int> containing the x and y coordinates for the monster spawn.
                 */
                static std::pair<int, int> getMonsterSpawnCoordinates(int window_width, int window_height, RandomNumber randomizer)
                {
                    return std::make_pair(window_width + 30, randomizer.generateRandomNumbers(300, window_height - 200));
                }

            protected:
            private:
        };

    }

#endif /* !PIPEFACTORY_HPP_ */
