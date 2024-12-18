/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RandomNumber
*/

#ifndef GENERATERANDOMNUMBER_HPP_
    #define GENERATERANDOMNUMBER_HPP_

    #include "../shared/Includes.hpp"

    namespace rtype {
        class RandomNumber {
            public:
                RandomNumber()
                {
                    std::srand(std::time(nullptr));
                }
                ~RandomNumber() {};

                int generateRandomNumbers(int min, int max)
                {
                    return( min + std::rand() % (max - min + 1));
                }

            protected:
            private:
        };
    }
#endif /* !RANDOMNUMBER_HPP_ */
