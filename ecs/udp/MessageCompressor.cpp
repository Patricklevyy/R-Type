/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MessageCompressor
*/

#include "MessageCompressor.hpp"

namespace ecs
{
    namespace udp
    {
        MessageCompressor::MessageCompressor()
        {
        }

        MessageCompressor::~MessageCompressor()
        {
        }

        void MessageCompressor::serialize(const Message &msg, std::vector<char> &buffer)
        {
            buffer.clear();

            unsigned short header = (msg.id & 0x3FF) | ((msg.action & 0x3F) << 10);
            buffer.push_back(header & 0xFF);
            buffer.push_back((header >> 8) & 0xFF);

            uint32_t paramsSize = msg.params.size();
            buffer.insert(buffer.end(), reinterpret_cast<const char *>(&paramsSize),
                          reinterpret_cast<const char *>(&paramsSize) + sizeof(paramsSize));
            buffer.insert(buffer.end(), msg.params.begin(), msg.params.end());

            uint32_t secretKeySize = msg.secret_key.size();
            buffer.insert(buffer.end(), reinterpret_cast<const char *>(&secretKeySize),
                          reinterpret_cast<const char *>(&secretKeySize) + sizeof(secretKeySize));
            buffer.insert(buffer.end(), msg.secret_key.begin(), msg.secret_key.end());
        }

        void MessageCompressor::deserialize(const std::vector<char> &buffer, Message &msg)
        {
            size_t offset = 0;

            const size_t minSize = 2 + sizeof(uint32_t) + sizeof(uint32_t);
            if (buffer.size() < minSize) {
                throw std::runtime_error("Buffer too small to contain a valid message");
            }

            unsigned short header = buffer[offset] | (buffer[offset + 1] << 8);
            msg.id = header & 0x3FF;
            msg.action = (header >> 10) & 0x3F;
            offset += 2;

            uint32_t paramsSize;
            if (buffer.size() < offset + sizeof(paramsSize)) {
                throw std::runtime_error("Buffer too small to contain params size");
            }
            std::memcpy(&paramsSize, &buffer[offset], sizeof(paramsSize));
            offset += sizeof(paramsSize);

            if (buffer.size() < offset + paramsSize) {
                throw std::runtime_error("Buffer too small to contain params");
            }
            msg.params = std::string(buffer.begin() + offset, buffer.begin() + offset + paramsSize);
            offset += paramsSize;

            uint32_t secretKeySize;
            if (buffer.size() < offset + sizeof(secretKeySize)) {
                throw std::runtime_error("Buffer too small to contain secret key size");
            }
            std::memcpy(&secretKeySize, &buffer[offset], sizeof(secretKeySize));
            offset += sizeof(secretKeySize);

            if (buffer.size() < offset + secretKeySize) {
                throw std::runtime_error("Buffer too small to contain secret key");
            }
            msg.secret_key = std::string(buffer.begin() + offset, buffer.begin() + offset + secretKeySize);
        }

    }
}