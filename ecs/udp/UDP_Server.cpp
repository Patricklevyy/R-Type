/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Server
*/

#include "UDP_Server.hpp"

namespace ecs
{
    namespace udp
    {
        UDP_Server::UDP_Server() : UDP_Manager() {}


        UDP_Server::~UDP_Server() {}

        std::string UDP_Server::generateClientKey(const sockaddr_in &addr) const
        {
            return std::string(inet_ntoa(addr.sin_addr)) + ":" + std::to_string(ntohs(addr.sin_port));
        }

        bool UDP_Server::initialize(const std::string &configFile, int port)
        {
            libconfig::Config cfg;

            try {
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
            }
            catch (const libconfig::SettingNotFoundException &e) {
                throw ecs::ERROR::WrongConfigurationExceptions();
            } catch (const libconfig::SettingTypeException &e) {
                throw ecs::ERROR::WrongConfigurationExceptions();
            }

            sockaddr_in addr{};
            addr.sin_family = AF_INET;
            addr.sin_port = htons(port);
            addr.sin_addr.s_addr = INADDR_ANY;

            sockfd = socket(AF_INET, SOCK_DGRAM, 0);
            if (sockfd < 0) {
                throw ecs::ERROR::SocketNotInitializedExceptions();
            }

            if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
                close(sockfd);
                sockfd = -1;
                throw ecs::ERROR::BindFailedExceptions();
            }

            std::cout << "Server initialized on port " << port << ". Ready to accept clients.\n";

            return true;
        }
    }
}