/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Utils
*/

#include "Utils.hpp"

namespace rtype
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
        if (type == SPRITES::PLAYER_SIMPLE_MISSILE
            || type == SPRITES::PLAYER_CHARGED_SHOOT)
            return true;
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

    std::string Utils::bonusInfoToString(
        const std::pair<float, float> &position, int direction_x,
        int direction_y, SPRITES sprite, int velocity)
    {
        std::string info = "";

        info += "x=" + std::to_string(position.first)
            + ";y=" + std::to_string(position.second);
        info += ";dir_x=" + std::to_string(direction_x)
            + ";dir_y=" + std::to_string(direction_y);
        info += ";v=" + std::to_string(velocity);
        info += ";type=" + std::to_string(sprite);

        return info;
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

    std::list<std::pair<std::size_t, std::pair<float, float>>>
    Utils::parse_update(const std::string &params)
    {
        std::list<std::pair<std::size_t, std::pair<float, float>>> parsed_data;

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

            parsed_data.emplace_back(id, std::make_pair(x, y));
        }

        return parsed_data;
    }

    std::vector<std::tuple<std::pair<float, float>, int, int>>
    Utils::parseUpdateEntities(const std::string &message)
    {
        std::vector<std::tuple<std::pair<float, float>, int, int>> result;
        std::stringstream ss(message);
        std::string block;

        while (std::getline(ss, block, ';')) {
            if (block.empty())
                continue;

            float x = 0.0f, y = 0.0f;
            int id = 0, type = 0;

            std::stringstream blockStream(block);
            std::string value;

            if (std::getline(blockStream, value, ','))
                x = std::stof(value);
            if (std::getline(blockStream, value, ','))
                y = std::stof(value);
            if (std::getline(blockStream, value, ','))
                id = std::stoi(value);
            if (std::getline(blockStream, value, ','))
                type = std::stoi(value);

            result.emplace_back(std::make_pair(x, y), id, type);
        }

        return result;
    }

    std::tuple<std::tuple<float, float, int>, int, int>
    Utils::parsePositionAndRoomPort(const std::string &input)
    {
        std::stringstream ss(input);
        std::string token;

        float x = 0.0f, y = 0.0f;
        int port = 0;
        int dif, health;

        std::getline(ss, token, ';');
        x = std::stof(token);

        std::getline(ss, token, ';');
        y = std::stof(token);

        std::getline(ss, token, ';');
        health = std::stoi(token);

        std::getline(ss, token, ';');
        port = std::stoi(token);

        std::getline(ss, token, ';');
        dif = std::stoi(token);

        return std::make_tuple(std::tuple(x, y, health), port, dif);
    }

    std::list<std::pair<std::size_t, int>> Utils::parse_update_life(
        const std::string &params)
    {
        std::list<std::pair<std::size_t, int>> parsed_data;

        std::stringstream ss(params);
        std::string block;

        while (std::getline(ss, block, ';')) {
            if (block.empty())
                continue;

            std::size_t id = 0;
            int value = 0;

            std::stringstream block_ss(block);
            std::string field;
            int index = 0;

            while (std::getline(block_ss, field, ',')) {
                if (index == 0) {
                    id = static_cast<std::size_t>(std::stoul(field));
                } else if (index == 1) {
                    value = std::stoi(field);
                }
                index++;
            }

            parsed_data.emplace_back(id, value);
        }

        return parsed_data;
    }

} // namespace rtype
