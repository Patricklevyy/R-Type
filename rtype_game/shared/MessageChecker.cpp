/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MessageChecker
*/

#include "MessageChecker.hpp"

namespace rtype
{
    MessageChecker::MessageChecker()
    {
    }

    MessageChecker::~MessageChecker()
    {
    }

    void MessageChecker::checkAction(const ecs::udp::Message &message) const
    {
        if (message.action < 0 || message.action >= MAX_ACTION) {
            std::string error_message =
                "Unknown action : " + std::to_string(message.action);
            throw ERROR::InvalidActionExceptions(error_message);
        }
    }

    std::map<std::string, std::string> MessageChecker::checkFormatParams(
        std::string &params)
    {
        std::map<std::string, std::string> paramMap;

        std::istringstream stream(params);
        std::string pair;

        while (std::getline(stream, pair, ';')) {
            size_t pos = pair.find('=');
            if (pos != std::string::npos) {
                std::string key = pair.substr(0, pos);
                std::string value = pair.substr(pos + 1);
                paramMap[key] = value;
            } else {
                throw ERROR::WrongFormatParamsExceptions(
                    "Must have format {key=value;key=value...}");
            }
        }

        return paramMap;
    }

    std::unordered_map<std::string, std::string> MessageChecker::parseResponse(
        const std::string &response)
    {
        std::unordered_map<std::string, std::string> parsedData;
        std::istringstream stream(response);
        std::string keyValuePair;

        while (std::getline(stream, keyValuePair, ';')) {
            size_t delimiterPos = keyValuePair.find('=');
            if (delimiterPos != std::string::npos) {
                std::string key = keyValuePair.substr(0, delimiterPos);
                std::string value = keyValuePair.substr(delimiterPos + 1);
                parsedData[key] = value;
            }
        }

        return parsedData;
    }
} // namespace rtype
