/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Utils
*/

#include "Utils.hpp"

namespace rtype
{
    std::tuple<ecs::direction, ecs::direction, size_t> Utils::extractPlayerPosIndex(std::string params, unsigned int player_id)
    {
        int x = 0, y = 0;

        size_t delimiter_pos = params.find(';');
        if (delimiter_pos != std::string::npos) {
            std::string x_part = params.substr(0, delimiter_pos);
            std::string y_part = params.substr(delimiter_pos + 1);

            if (x_part.find("x=") == 0) {
                x = std::stoi(x_part.substr(2));
            }

            if (y_part.find("y=") == 0) {
                y = std::stoi(y_part.substr(2));
            }
        }
        return std::tuple<ecs::direction, ecs::direction, size_t>(static_cast<ecs::direction>(x), static_cast<ecs::direction>(y), player_id);
    }
}