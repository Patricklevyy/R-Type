/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Utils
*/

#include "Utils.hpp"

namespace poc_game
{
    void Utils::checkAction(int action)
    {
        if (action < 0 || action >= MAX_ACTION) {
            std::string error_message =
                "Unknown action : " + std::to_string(action);
            throw ERROR::InvalidActionExceptions(error_message);
        }
    }

    std::tuple<ecs::direction, ecs::direction, size_t>
    Utils::extractPlayerPosIndex(std::string params, unsigned int player_id)
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
        return std::tuple<ecs::direction, ecs::direction, size_t>(
            static_cast<ecs::direction>(x), static_cast<ecs::direction>(y),
            player_id);
    }

    std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES>
    Utils::extractProjectilePosAndDir(std::string params)
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

        int spriteValue = std::stoi(parts[4].substr(parts[4].find('=') + 1));
        SPRITES type_shoot = static_cast<SPRITES>(spriteValue);

        return std::make_tuple(
            std::make_pair(x, y), std::make_pair(dir_x, dir_y), type_shoot);
    }

    std::map<std::string, std::string> Utils::parseMessageParams(
        const std::string &params)
    {
        std::map<std::string, std::string> parsedParams;
        std::stringstream ss(params);
        std::string token;

        while (std::getline(ss, token, ';')) {
            size_t pos = token.find('=');
            if (pos != std::string::npos) {
                std::string key = token.substr(0, pos);
                std::string value = token.substr(pos + 1);
                parsedParams[key] = value;
            }
        }

        return parsedParams;
    }

    bool Utils::isAllie(SPRITES type)
    {
        // if (type == SPRITES::PLAYER_SIMPLE_MISSILE)
        //     return true;
        return false;
    }

    std::string Utils::projectilesInfoToString(
        std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES>
            pos_dir_sprite,
        int velocity)
    {
        std::string info = "";

        info += "x=" + std::to_string(std::get<0>(pos_dir_sprite).first)
            + ";y=" + std::to_string(std::get<0>(pos_dir_sprite).second);
        info += ";dir_x=" + std::to_string(std::get<1>(pos_dir_sprite).first)
            + ";dir_y=" + std::to_string(std::get<1>(pos_dir_sprite).second);
        info += ";v=" + std::to_string(velocity);
        info += ";type=" + std::to_string(std::get<2>(pos_dir_sprite));

        return info;
    }

    std::tuple<float, float, int> Utils::parsePositionAndRoomPort(
        const std::string &input)
    {
        std::stringstream ss(input);
        std::string token;

        float x = 0.0f, y = 0.0f;
        int port = 0;

        std::getline(ss, token, ';');
        x = std::stof(token);

        std::getline(ss, token, ';');
        y = std::stof(token);

        std::getline(ss, token, ';');
        port = std::stoi(token);

        return std::make_tuple(x, y, port);
    }

    std::list<std::tuple<std::size_t, float, float>> Utils::parse_update(
        const std::string &params)
    {
        std::list<std::tuple<std::size_t, float, float>> parsed_data;

        std::stringstream ss(params);
        std::string block;

        while (std::getline(ss, block, ';')) {
            if (block.empty())
                continue;

            std::size_t id = 0;
            float x = 0.0f, y = 0.0f;

            std::stringstream block_ss(block);
            std::string value;
            int index = 0;

            while (std::getline(block_ss, value, ',')) {
                switch (index) {
                    case 0:
                        id = static_cast<std::size_t>(std::stoul(value));
                        break;
                    case 1: x = std::stof(value); break;
                    case 2: y = std::stof(value); break;
                    default: break;
                }
                index++;
            }

            parsed_data.emplace_back(id, x, y);
        }

        return parsed_data;
    }

    std::string Utils::check_adress(int port, const std::string &server_ip)
    {
        std::cout << "servir ipp" << server_ip << std::endl;
        std::cout << "servir ipp" << server_ip << std::endl;
        if (port == 0)
            throw ERROR::MissingPortParamsExceptions("Missing 'port'");
        std::string portStr = std::to_string(port);
        return (server_ip + ":" + portStr);
    }
} // namespace poc_game