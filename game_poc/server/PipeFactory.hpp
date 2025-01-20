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
        class PipeFactory {
        public:
                static std::pair<int, int> getMonsterSpawnCoordinates(int window_width, int window_height, RandomNumber randomizer)
                {
                    return std::make_pair(window_width + 30, randomizer.generateRandomNumbers(300, window_height - 200));
                }

            protected:
            private:
        };

    }

#endif /* !PIPEFACTORY_HPP_ */
