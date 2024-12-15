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

    std::pair<std::pair<float, float>, std::pair<int, int>> Utils::extractProjectilePosAndDir(std::string params)
    {
        float x = 0.0f, y = 0.0f;
        int dir_x = 0, dir_y = 0;

        std::stringstream ss(params);
        std::string segment;
        std::vector<std::string> parts;

        while (std::getline(ss, segment, ';')) {
            parts.push_back(segment);
        }

        x = std::stof(parts[0].substr(parts[0].find('=') + 1));
        y = std::stof(parts[1].substr(parts[1].find('=') + 1));
        dir_x = std::stoi(parts[2].substr(parts[2].find('=') + 1));
        dir_y = std::stoi(parts[3].substr(parts[3].find('=') + 1));

        return std::make_pair(std::make_pair(x, y), std::make_pair(dir_x, dir_y));
    }
}
