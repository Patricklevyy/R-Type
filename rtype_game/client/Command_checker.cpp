/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_checker
*/

#include "Command_checker.hpp"

namespace rtype
{
    std::string Command_checker::check_adress(int port, const std::string &server_ip)
    {
        std::cout << "servir ipp" << server_ip << std::endl;
        std::cout << "servir ipp" << server_ip << std::endl;
        if (port == 0)
            throw ERROR::MissingPortParamsExceptions("Missing 'port'");
        std::string portStr = std::to_string(port);
        return (server_ip + ":" + portStr);
    }

    std::list<std::pair<std::size_t, std::pair<float, float>>> Command_checker::parse_update(const std::string &params) {
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
                    case 1:
                        x = std::stof(value);
                        break;
                    case 2:
                        y = std::stof(value);
                        break;
                    default:
                        break;
                }
                index++;
            }

            parsed_data.emplace_back(id, std::make_pair(x, y));
        }

        return parsed_data;
    }

    std::vector<std::tuple<std::pair<float, float>, int, int>> Command_checker::parseUpdateEntities(const std::string &message)
    {
        std::vector<std::tuple<std::pair<float, float>, int, int>> result;
        std::stringstream ss(message);
        std::string block;

        while (std::getline(ss, block, ';')) {
            if (block.empty()) continue;

            float x = 0.0f, y = 0.0f;
            int id = 0, type = 0;

            std::stringstream blockStream(block);
            std::string value;

            if (std::getline(blockStream, value, ',')) x = std::stof(value);
            if (std::getline(blockStream, value, ',')) y = std::stof(value);
            if (std::getline(blockStream, value, ',')) id = std::stoi(value);
            if (std::getline(blockStream, value, ',')) type = std::stoi(value);

            result.emplace_back(std::make_pair(x, y), id, type);
        }

        return result;
    }

    std::tuple<std::pair<float, float>, int, int> Command_checker::parsePositionAndRoomPort(const std::string &input)
    {
        std::stringstream ss(input);
        std::string token;

        float x = 0.0f, y = 0.0f;
        int port = 0; int dif;

        std::getline(ss, token, ';');
        x = std::stof(token);

        std::getline(ss, token, ';');
        y = std::stof(token);

        std::getline(ss, token, ';');
        port = std::stoi(token);

        std::getline(ss, token, ';');
        dif = std::stoi(token);

        return std::make_tuple(std::make_pair(x, y), port, dif);
    }
}