/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <iostream>
    #include "../../ecs/Enums_ecs.hpp"
    #include <vector>
    #include <tuple>
    #include <sstream>
    #include "Enums.hpp"
    #include "RTypeExceptions.hpp"
    #include "Includes.hpp"

    namespace rtype
    {
        class Utils {
            public:
                static std::map<std::string, std::string> parseMessageParams(const std::string &params);

                static void checkAction(int);

                static std::tuple<ecs::direction, ecs::direction, size_t> extractPlayerPosIndex(std::string, unsigned int);

                static std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> extractProjectilePosAndDir(std::string);

            protected:
            private:
        };
    }

#endif /* !UTILS_HPP_ */
