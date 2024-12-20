/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MonsterFactory
*/

#ifndef MONSTERFACTORY_HPP_
    #define MONSTERFACTORY_HPP_

    #include "RandomNumber.hpp"
    #include "../shared/Enums.hpp"

    namespace rtype
    {
        class MonsterFactory {
        public:
                static std::pair<int, int> getMonsterSpawnCoordinates(int window_width, int window_height, RandomNumber randomizer)
                {
                    return std::make_pair(window_width + 30, randomizer.generateRandomNumbers(20, window_height - 100));
                }

                static int getMonsterVelocity(SPRITES sprite)
                {
                    switch (sprite)
                    {
                    case SPRITES::SIMPLE_MONSTER:
                        return 80;
                    case SPRITES::ADVANCED_MONSTER:
                        return 100;
                    default:
                        throw std::invalid_argument("Invalid sprite ID for monster velocity : " + sprite);
                        break;
                    }
                }

                static int getMonsterLife(SPRITES sprite)
                {
                    switch (sprite)
                    {
                    case SPRITES::SIMPLE_MONSTER:
                        return 60;
                    case SPRITES::ADVANCED_MONSTER:
                        return 100;
                    default:
                        throw std::invalid_argument("Invalid sprite ID for monster life: " + sprite);
                        break;
                    }
                }

            protected:
            private:
        };

    }
#endif /* !MONSTERFACTORY_HPP_ */
