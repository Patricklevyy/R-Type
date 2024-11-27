/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Server
*/

#include "UDP_Server.hpp"

#include "UDP_Server.hpp"
#include <iostream>
#include <arpa/inet.h>

// Constructeur
UDP_Server::UDP_Server() : UDP_Manager() {}

// Destructeur
UDP_Server::~UDP_Server() {}

// bool UDP_Server::addClient(const sockaddr_in &clientAddr, const std::string &message)
// {
//     std::string clientKey = generateClientKey(clientAddr);

//     if (clients.find(clientKey) != clients.end()) {
//         std::cerr << "Client " << clientKey << " is already registered.\n";
//         return false;
//     }

//     clients[clientKey] = clientAddr;
//     std::cout << "Client " << clientKey << " added.\n";

//     lastSenderAddr = clientAddr;
//     return sendMessage(message);
// }

// // Afficher tous les clients connectés
// void UDP_Server::listClients() const
// {
//     if (clients.empty()) {
//         std::cout << "No clients connected.\n";
//         return;
//     }

//     std::cout << "Connected clients:\n";
//     for (const auto &[key, addr] : clients) {
//         std::cout << "- " << key << "\n";
//     }
// }

// Générer une clé unique pour chaque client
std::string UDP_Server::generateClientKey(const sockaddr_in &addr) const
{
    return std::string(inet_ntoa(addr.sin_addr)) + ":" + std::to_string(ntohs(addr.sin_port));
}

bool UDP_Server::initialize(const std::string &configFile, int port)
{
    // Initialisation de la configuration du fichier
    libconfig::Config cfg;

    try
    {
        std::cout << "Loading config file: " << configFile.c_str() << std::endl;
        cfg.readFile(configFile.c_str());
    }
    catch (const libconfig::FileIOException &e)
    {
        std::cerr << "Error reading configuration file: " << e.what() << std::endl;
        return false;
    }
    catch (const libconfig::ParseException &e)
    {
        std::cerr << "Error parsing configuration file: " << e.getError() << std::endl;
        return false;
    }

    const libconfig::Setting &root = cfg.getRoot();

    try
    {
        const libconfig::Setting &udpSettings = root["UDP"];
        bufferSize = udpSettings["buffer_size"];

        if (bufferSize > 1472) { // Limite de taille de buffer
            std::cerr << "Buffer size exceeds safe UDP message size (1472 bytes).\n";
            return false;
        }
    }
    catch (const libconfig::SettingNotFoundException &e)
    {
        std::cerr << "Missing setting in configuration file: " << e.what() << "\n";
        return false;
    }
    catch (const libconfig::SettingTypeException &e)
    {
        std::cerr << "Type mismatch in configuration file: " << e.what() << "\n";
        return false;
    }

    // Initialisation de la socket UDP
    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);  // Utilisation du port passé en paramètre
    addr.sin_addr.s_addr = INADDR_ANY;  // Ecouter sur toutes les interfaces

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        perror("Socket creation failed");
        return false;
    }

    // Binding sur l'adresse et le port spécifiés
    if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        sockfd = -1;
        return false;
    }

    std::cout << "Server initialized on port " << port << ". Ready to accept clients.\n";

    return true;
}
