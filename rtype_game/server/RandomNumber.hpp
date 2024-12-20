/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RandomNumber
*/

/**
 * @file RandomNumber.hpp
 * @brief Provides utilities for generating random numbers.
 */

#ifndef GENERATERANDOMNUMBER_HPP_
    #define GENERATERANDOMNUMBER_HPP_

    #include "../shared/Includes.hpp"

    namespace rtype {

        /**
        * @class RandomNumber
        * @brief Utility class for generating random numbers within a range.
        */
        class RandomNumber {
            public:
                /**
                * @brief Constructor that initializes the random number generator.
                */
                RandomNumber()
                {
                    std::srand(std::time(nullptr));
                }

                /**
                * @brief Destructor for RandomNumber.
                */
                ~RandomNumber() {};

                /**
                 * @brief Generates a random integer within a specified range.
                 * @param min The minimum value of the range.
                 * @param max The maximum value of the range.
                 * @return A random integer between min and max.
                 */
                int generateRandomNumbers(int min, int max)
                {
                    return( min + std::rand() % (max - min + 1));
                }

            protected:
            private:
        };
    }
#endif /* !RANDOMNUMBER_HPP_ */
