/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MessageCompressor
*/

#include "MessageCompressor.hpp"

MessageCompressor::MessageCompressor()
{
}

MessageCompressor::~MessageCompressor()
{
}

void MessageCompressor::serialize(const Message& msg, std::vector<char>& buffer)
{
    buffer.clear();

    unsigned short header = (msg.id & 0x3FF) | ((msg.action & 0x3F) << 10);
    buffer.push_back(header & 0xFF);
    buffer.push_back((header >> 8) & 0xFF);

    uint32_t paramsSize = msg.params.size();
    buffer.insert(buffer.end(), reinterpret_cast<const char*>(&paramsSize),
                  reinterpret_cast<const char*>(&paramsSize) + sizeof(paramsSize));
    buffer.insert(buffer.end(), msg.params.begin(), msg.params.end());

    uint32_t bodySize = msg.body.size();
    buffer.insert(buffer.end(), reinterpret_cast<const char*>(&bodySize),
                  reinterpret_cast<const char*>(&bodySize) + sizeof(bodySize));
    buffer.insert(buffer.end(), msg.body.begin(), msg.body.end());
}

void MessageCompressor::deserialize(const std::vector<char>& buffer, Message& msg) {
    size_t offset = 0;

    unsigned short header = buffer[offset] | (buffer[offset + 1] << 8);
    msg.id = header & 0x3FF;
    msg.action = (header >> 10) & 0x3F;
    offset += 2;

    uint32_t paramsSize;
    std::memcpy(&paramsSize, &buffer[offset], sizeof(paramsSize));
    offset += sizeof(paramsSize);
    msg.params = std::string(buffer.begin() + offset, buffer.begin() + offset + paramsSize);
    offset += paramsSize;

    uint32_t bodySize;
    std::memcpy(&bodySize, &buffer[offset], sizeof(bodySize));
    offset += sizeof(bodySize);
    msg.body = std::string(buffer.begin() + offset, buffer.begin() + offset + bodySize);
    offset += bodySize;
}
