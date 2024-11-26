/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

#ifndef UDP_MANAGER_HPP
#define UDP_MANAGER_HPP

#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <libconfig.h++>

class UDP_Manager {
public:
    // Constructeur et destructeur
    UDP_Manager();
    ~UDP_Manager();

    // Méthodes publiques
    bool initialize(const std::string& configFile, bool isServer);
    bool sendMessage(const std::string& message);
    bool receiveMessage(std::string& message);
    bool respond(const std::string& message);
    std::string getLastClientAddress() const;

private:
    // Attributs privés
    int sockfd;  // Socket file descriptor
    int bufferSize;  // Taille du buffer pour les messages
    sockaddr_in serverAddr;  // Adresse du serveur
    sockaddr_in lastSenderAddr;  // Adresse du dernier expéditeur
    bool lastSenderValid;  // Indicateur de la validité de l'expéditeur
    std::string clientAddrStr;  // Chaîne représentant l'adresse du dernier client

    // Méthodes privées
    bool setupServer(const libconfig::Setting& udpSettings);
    bool setupClient(const libconfig::Setting& udpSettings);
};

#endif // UDP_MANAGER_HPP
