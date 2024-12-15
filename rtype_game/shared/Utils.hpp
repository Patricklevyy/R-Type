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

    namespace rtype
    {
        class Utils {
            public:
                static std::tuple<ecs::direction, ecs::direction, size_t> extractPlayerPosIndex(std::string, unsigned int);

                static std::pair<std::pair<float, float>, std::pair<int, int>> extractProjectilePosAndDir(std::string);

            protected:
            private:
        };
    }

#endif /* !UTILS_HPP_ */
