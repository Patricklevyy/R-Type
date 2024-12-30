/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Client
*/

#include "UDP_Client.hpp"

namespace ecs
{
    namespace udp
    {
        UDP_Client::UDP_Client()
        {
        }

        UDP_Client::~UDP_Client()
        {
        }

        std::string UDP_Client::getServerIp() const
        {
            return _ip_server;
        }

        void UDP_Client::setDefaultAddress(const std::string &address)
        {
            defaultAddress = address;
        }

        bool UDP_Client::sendMessageToDefault(const std::vector<char> message)
        {
            if (defaultAddress.empty()) {
                std::cerr << "[ERROR] Default address is not set!" << std::endl;
                return false;
            }
            return sendMessage(message, defaultAddress);
        }

        bool UDP_Client::initialize(const std::string &configFile, int port)
        {
            libconfig::Config cfg;

            try {
                std::cout << configFile.c_str() << std::endl;
                cfg.readFile(configFile.c_str());
            } catch (const libconfig::FileIOException &e) {
                std::cerr << "Error reading configuration file: " << e.what()
                          << std::endl;
                return false;
            } catch (const libconfig::ParseException &e) {
                std::cerr << "Error parsing configuration file: "
                          << e.getError() << std::endl;
                return false;
            }

            const libconfig::Setting &root = cfg.getRoot();

            try {
                const libconfig::Setting &udpSettings = root["UDP"];
                bufferSize = udpSettings["buffer_size"];

                if (udpSettings.exists("secrete_key_rtype")) {
                    secret_key = udpSettings["secrete_key_rtype"].c_str();
                    std::cout << "Clé secrète HMAC lue : " << secret_key
                              << std::endl;
                } else {
                    std::cerr
                        << "Clé secrète HMAC manquante dans la configuration."
                        << std::endl;
                    return false;
                }

                if (bufferSize > 1472) {
                    throw ecs::ERROR::WrongBufferSizeExceptions();
                }

                sockaddr_in addr{};
                addr.sin_family = AF_INET;

                const libconfig::Setting &clientSettings =
                    udpSettings["client"];
                std::string ip = clientSettings["ip"];
                int port = clientSettings["port"];
                addr.sin_port = htons(port);
                inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

                const libconfig::Setting &serverSettings =
                    udpSettings["server"];
                std::string serverIp = serverSettings["ip"];
                _ip_server = serverIp;
                int serverPort = serverSettings["port"];
                setDefaultAddress(serverIp + ":" + std::to_string(serverPort));
                serverAddr.sin_family = AF_INET;
                serverAddr.sin_port = htons(serverPort);
                inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr);

                sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                if (sockfd < 0) {
                    throw ecs::ERROR::SocketNotInitializedExceptions();
                }
                int flags = fcntl(sockfd, F_GETFL, 0);
                if (flags < 0
                    || fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
                    close(sockfd);
                    sockfd = -1;
                    throw ecs::ERROR::SocketNotInitializedExceptions();
                }

                if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
                    close(sockfd);
                    sockfd = -1;
                    throw ecs::ERROR::BindFailedExceptions();
                }

                std::cout << "Client initialized to connect to " << serverIp
                          << ":" << serverPort << "\n";
            } catch (const libconfig::SettingNotFoundException &e) {
                std::cerr << "Missing setting in configuration file: "
                          << e.what() << "\n";
                return false;
            } catch (const libconfig::SettingTypeException &e) {
                std::cerr << "Type mismatch in configuration file: " << e.what()
                          << "\n";
                return false;
            }

            return true;
        }
    } // namespace udp
} // namespace ecs