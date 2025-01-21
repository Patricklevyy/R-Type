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
         * @brief Factory class for generating pipes for flappy bird.
         */
        class PipeFactory {
        public:
                /**
                 * @brief Calculates the spawn coordinates for a monster.
                 * @param window_width The width of the game window.
                 * @param window_height The height of the game window.
                 * @param randomizer A RandomNumber object used to generate a random y coordinate within a specified range.
                 * @return A pair of integers representing the x and y coordinates of the monster spawn position.
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
