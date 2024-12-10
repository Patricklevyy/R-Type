/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_checker
*/

#include "Command_checker.hpp"

namespace rtype
{
    std::string Command_checker::check_adress(std::map<std::string, std::string>& params)
    {
        if (params.find("port") == params.end())
            throw ERROR::MissingPortParamsExceptions("Missing 'port'");
        std::string ip = "127.0.0.1:";
        std::string port = params["port"];
        return ip + port;
    }
}
