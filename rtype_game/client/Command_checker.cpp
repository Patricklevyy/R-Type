/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_checker
*/

#include "Command_checker.hpp"

namespace rtype
{
    std::string Command_checker::check_adress(std::map<std::string, std::string> &params, std::string server_ip)
    {
        if (params.find("port") == params.end())
            throw ERROR::MissingPortParamsExceptions("Missing 'port'");
        std::string ip = "127.0.0.1:";
        std::string port = params["port"];
        return ip + port;
    }

    std::list<std::tuple<std::size_t, std::pair<float, float>, int>> Command_checker::parse_update(std::string params)
    {
        std::list<std::tuple<std::size_t, std::pair<float, float>, int>> parsed_data;

        std::stringstream ss(params);
        std::string block;
        while (std::getline(ss, block, ';')) {
            if (block.empty())
                continue;

            std::size_t id = 0;
            float x = 0.0f, y = 0.0f;
            int health = 0;

            std::stringstream block_ss(block);
            std::string pair;
            while (std::getline(block_ss, pair, ',')) {
                auto equal_pos = pair.find('=');
                if (equal_pos != std::string::npos) {
                    std::string key = pair.substr(0, equal_pos);
                    std::string value = pair.substr(equal_pos + 1);

                    if (key == "id") {
                        id = static_cast<std::size_t>(std::stoul(value));
                    } else if (key == "x") {
                        x = std::stof(value);
                    } else if (key == "y") {
                        y = std::stof(value);
                    } else if (key == "health") {
                        health = std::stoi(value);
                    }
                }
            }

            parsed_data.emplace_back(id, std::make_pair(x, y), health);
        }
        return parsed_data;
    }
}