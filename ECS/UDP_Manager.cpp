/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

#include "UDP_Manager.hpp"

UDP_Manager::UDP_Manager() : sockfd(-1), bufferSize(1472), lastSenderValid(false)
{
}

UDP_Manager::~UDP_Manager()
{
    if (sockfd >= 0)
        close(sockfd);
}

bool UDP_Manager::initialize(const std::string& configFile, bool isServer) {
    libconfig::Config cfg;

            try {
                std::cout << configFile.c_str() << std::endl;
                cfg.readFile(configFile.c_str());
            } catch (const libconfig::FileIOException& e) {
                std::cerr << "Error reading configuration file: " << e.what() << std::endl;
                return false;
            } catch (const libconfig::ParseException& e) {
                std::cerr << "Error parsing configuration file: " << e.getError() << std::endl;
                return false;
            }

            const libconfig::Setting& root = cfg.getRoot();

            try {
                // Obtenir les paramètres UDP
                const libconfig::Setting& udpSettings = root["UDP"];
                bufferSize = udpSettings["buffer_size"];

                // Vérifier la taille du buffer
                if (bufferSize > 1472) {
                    std::cerr << "Buffer size exceeds safe UDP message size (1472 bytes).\n";
                    return false;
                }

                sockaddr_in addr{};
                addr.sin_family = AF_INET;

                if (isServer) {
                    // Configuration pour le serveur
                    const libconfig::Setting& serverSettings = udpSettings["server"];
                    std::string ip = serverSettings["ip"];
                    int port = serverSettings["port"];
                    addr.sin_port = htons(port);
                    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

                    // Créer le socket
                    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                    if (sockfd < 0) {
                        perror("Socket creation failed");
                        return false;
                    }

                    // Lier le socket à l'adresse et au port
                    if (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
                        perror("Bind failed");
                        close(sockfd);
                        sockfd = -1;
                        return false;
                    }

                    std::cout << "Server is running on " << ip << ":" << port << "\n";
                } else {
                    // Configuration pour le client
                    const libconfig::Setting& clientSettings = udpSettings["client"];
                    std::string ip = clientSettings["ip"];
                    int port = clientSettings["port"];
                    addr.sin_port = htons(port);
                    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

                    // Stocker l'adresse du serveur
                    const libconfig::Setting& serverSettings = udpSettings["server"];
                    std::string serverIp = serverSettings["ip"];
                    int serverPort = serverSettings["port"];
                    serverAddr.sin_family = AF_INET;
                    serverAddr.sin_port = htons(serverPort);
                    inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr);

                    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                    if (sockfd < 0) {
                        perror("Socket creation failed");
                        return false;
                    }

                    std::cout << "Client initialized to connect to " << serverIp << ":" << serverPort << "\n";
                }
            } catch (const libconfig::SettingNotFoundException& e) {
                std::cerr << "Missing setting in configuration file: " << e.what() << "\n";
                return false;
            } catch (const libconfig::SettingTypeException& e) {
                std::cerr << "Type mismatch in configuration file: " << e.what() << "\n";
                return false;
            }

            return true;
}

bool UDP_Manager::sendMessage(const std::string& message) {
                if (sockfd < 0) {
                    std::cerr << "Socket not initialized.\n";
                    return false;
                }
                if (message.size() > bufferSize) {
                    std::cerr << "Message exceeds buffer size. Truncating.\n";
                }
                std::cout << "je send du server" << std::endl;
                ssize_t sent = sendto(sockfd, message.c_str(), std::min(bufferSize, (int)message.size()), 0,
                                    (struct sockaddr*)&serverAddr, sizeof(serverAddr));
                return sent >= 0;
            }

bool UDP_Manager::receiveMessage(std::string& message) {
    if (sockfd < 0) {
        std::cerr << "Socket not initialized.\n";
        return false;
    }

    char buffer[bufferSize];
    sockaddr_in senderAddr{};
    socklen_t senderLen = sizeof(senderAddr);
    ssize_t received = recvfrom(sockfd, buffer, bufferSize, 0, (struct sockaddr*)&senderAddr, &senderLen);

    if (received < 0) {
        perror("Recvfrom failed");
        return false;
    }

    // Stocke le dernier expéditeur
    lastSenderAddr = senderAddr;
    lastSenderValid = true;

    message.assign(buffer, received);
    clientAddrStr = std::string(inet_ntoa(senderAddr.sin_addr)) + ":" + std::to_string(ntohs(senderAddr.sin_port));
    return true;
}



std::string UDP_Manager::getLastClientAddress() const {
                return clientAddrStr;
            }

bool UDP_Manager::respond(const std::string& message) {
    if (sockfd < 0) {
        std::cerr << "Socket not initialized.\n";
        return false;
    }

    if (!lastSenderValid) {
        std::cerr << "No valid last sender address to respond to.\n";
        return false;
    }

    if (message.size() > bufferSize) {
        std::cerr << "Message exceeds buffer size. Truncating.\n";
    }

    ssize_t sent = sendto(sockfd, message.c_str(), std::min(bufferSize, (int)message.size()), 0,
                          (struct sockaddr*)&lastSenderAddr, sizeof(lastSenderAddr));
    return sent >= 0;
}