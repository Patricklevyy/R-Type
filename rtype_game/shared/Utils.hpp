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
    #include <tuple>

    namespace rtype
    {
        class Utils {
            public:
                static std::tuple<ecs::direction, ecs::direction, size_t> extractPlayerPosIndex(std::string, unsigned int);

            protected:
            private:
        };
    }

#endif /* !UTILS_HPP_ */
