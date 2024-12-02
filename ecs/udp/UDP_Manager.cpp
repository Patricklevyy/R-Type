/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

#include "UDP_Manager.hpp"

namespace ecs
{
    namespace udp
    {
        UDP_Manager::UDP_Manager() : sockfd(-1), bufferSize(1472), lastSenderValid(false)
        {
        }

        UDP_Manager::~UDP_Manager()
        {
            if (sockfd >= 0)
                close(sockfd);
        }

        bool UDP_Manager::initialize(const std::string &configFile, int port)
        {
            libconfig::Config cfg;

            try {
                std::cout << configFile.c_str() << std::endl;
                cfg.readFile(configFile.c_str());
            } catch (const libconfig::FileIOException &e) {
                throw ecs::ERROR::CantReadConfigFileExceptions();
            } catch (const libconfig::ParseException &e) {
                throw ecs::ERROR::CantParseConfigFileExceptions();
            }

            const libconfig::Setting &root = cfg.getRoot();

            try
            {
                const libconfig::Setting &udpSettings = root["UDP"];
                bufferSize = udpSettings["buffer_size"];

                if (bufferSize > 1472) {
                    throw ecs::ERROR::WrongBufferSizeExceptions();
                }

                sockaddr_in addr{};
                addr.sin_family = AF_INET;

                const libconfig::Setting &serverSettings = udpSettings["server"];
                    std::string ip = serverSettings["ip"];
                    int port = serverSettings["port"];
                    addr.sin_port = htons(port);
                    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

                    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                    if (sockfd < 0) {
                        throw ecs::ERROR::SocketNotInitializedExceptions();
                    }

                    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                        close(sockfd);
                        sockfd = -1;
                        throw ecs::ERROR::BindFailedExceptions();
                    }

                    std::cout << "Server is running on " << ip << ":" << port << "\n";
            } catch (const libconfig::SettingNotFoundException &e) {
                throw ecs::ERROR::WrongConfigurationExceptions();
            } catch (const libconfig::SettingTypeException &e) {
                throw ecs::ERROR::WrongConfigurationExceptions();
            }

            return true;
        }

        bool UDP_Manager::receiveMessage(std::vector<char>& message)
        {
            if (sockfd < 0) {
                throw ecs::ERROR::SocketNotInitializedExceptions();
            }

            char buffer[bufferSize];
            sockaddr_in senderAddr{};
            socklen_t senderLen = sizeof(senderAddr);
            ssize_t received = recvfrom(sockfd, buffer, bufferSize, 0, (struct sockaddr *)&senderAddr, &senderLen);

            if (received < 0) {
                throw ecs::ERROR::RecvExceptions();
            }

            lastSenderAddr = senderAddr;
            lastSenderValid = true;

            message.assign(buffer, buffer + received);

            clientAddrStr = std::string(inet_ntoa(senderAddr.sin_addr)) + ":" + std::to_string(ntohs(senderAddr.sin_port));
            return true;
        }


        std::string UDP_Manager::getLastClientAddress() const
        {
            return clientAddrStr;
        }

        bool UDP_Manager::sendMessage(const std::vector<char>& message, const std::string &address)
        {
            if (sockfd < 0) {
                throw ecs::ERROR::SocketNotInitializedExceptions();
            }

            size_t colonPos = address.find(':');
            if (colonPos == std::string::npos) {
                throw ecs::ERROR::InvalidAdressFormatExceptions();
            }

            std::string ip = address.substr(0, colonPos);
            int port = std::stoi(address.substr(colonPos + 1));

            sockaddr_in receiverAddr{};
            receiverAddr.sin_family = AF_INET;
            receiverAddr.sin_port = htons(port);
            if (inet_pton(AF_INET, ip.c_str(), &receiverAddr.sin_addr) <= 0) {
                throw ecs::ERROR::InvalidAdressFormatExceptions();
            }

            if (message.size() > bufferSize) {
                throw ecs::ERROR::MessageTooBigExceptions();
            }

            ssize_t sent = sendto(sockfd, message.data(), std::min(bufferSize, (int)message.size()), 0,
                                (struct sockaddr *)&receiverAddr, sizeof(receiverAddr));
            return sent >= 0;
        }
    }
}