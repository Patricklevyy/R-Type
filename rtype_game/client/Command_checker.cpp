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

    std::list<std::tuple<std::size_t, std::pair<float, float>, int>> Command_checker::parse_update(std::string params) {
        std::list<std::tuple<std::size_t, std::pair<float, float>, int>> parsed_data;

        std::stringstream ss(params);
        std::string block;

        // Séparation des blocs individuels par ';'
        while (std::getline(ss, block, ';')) {
            if (block.empty())
                continue;

            std::size_t id = 0;
            float x = 0.0f, y = 0.0f;
            int health = 0;

            std::stringstream block_ss(block);
            std::string value;
            int index = 0; // Pour savoir quelle donnée on traite

            // Séparation des valeurs par ','
            while (std::getline(block_ss, value, ',')) {
                switch (index) {
                    case 0: // ID
                        id = static_cast<std::size_t>(std::stoul(value));
                        break;
                    case 1: // X
                        x = std::stof(value);
                        break;
                    case 2: // Y
                        y = std::stof(value);
                        break;
                    case 3: // Health
                        health = std::stoi(value);
                        break;
                    default:
                        break;
                }
                index++;
            }

            // Ajouter les données dans la liste
            parsed_data.emplace_back(id, std::make_pair(x, y), health);
        }

        return parsed_data;
    }
}