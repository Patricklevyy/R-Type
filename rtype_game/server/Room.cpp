/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

#include "Room.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

namespace rtype
{

    Room::Room(int port, const std::string &name)
        : _port(port), _name(name), _sockfd(-1) {}

    Room::~Room()
    {
        if (_sockfd >= 0)
        {
            close(_sockfd);
        }
        if (_listenThread.joinable())
        {
            _listenThread.join(); // Joindre le thread si nécessaire
        }
    }

    Room::Room(Room &&other) noexcept
        : _port(other._port), _name(std::move(other._name)), _sockfd(other._sockfd), _addr(other._addr), _listenThread(std::move(other._listenThread))
    {
        other._sockfd = -1; // L'autre socket n'est plus valide
    }

    Room &Room::operator=(Room &&other) noexcept
    {
        if (this != &other)
        {
            _port = other._port;
            _name = std::move(other._name);
            _sockfd = other._sockfd;
            _addr = other._addr;
            _listenThread = std::move(other._listenThread);

            other._sockfd = -1;
        }
        return *this;
    }

    bool Room::initializeSocket()
    {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            std::cerr << "Socket creation failed for room " << _name << std::endl;
            return false;
        }

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        _addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
        {
            std::cerr << "Bind failed for room " << _name << std::endl;
            close(_sockfd);
            return false;
        }

        std::cout << "Room " << _name << " is listening on port " << _port << std::endl;
        return true;
    }

    void Room::listenForMessages()
    {
        char buffer[1024];
        sockaddr_in senderAddr;
        socklen_t senderLen = sizeof(senderAddr);

        while (true)
        {
            ssize_t received = recvfrom(_sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&senderAddr, &senderLen);
            if (received > 0)
            {
                std::string message(buffer, received);
                std::cout << "Received message in room thread " << _name << ": " << message << std::endl;

                // Si le message est une demande de création de client, envoyer l'adresse de la room
                if (message == "CREATE")
                {
                    // Convertir l'adresse du client en "ip:port"
                    char ipStr[INET_ADDRSTRLEN];
                    inet_ntop(AF_INET, &(senderAddr.sin_addr), ipStr, INET_ADDRSTRLEN);
                    int clientPort = ntohs(senderAddr.sin_port);

                    std::string clientAddress = std::string(ipStr) + ":" + std::to_string(clientPort);

                    // Formater l'adresse de la room
                    std::string roomAddress = "127.0.0.1:" + std::to_string(_port); // L'adresse et le port de la room

                    // Construire le message à envoyer
                    std::string response = "The room address is: " + roomAddress;

                    // Envoyer la réponse avec l'adresse de la room au client
                    if (!_udpServer.sendMessage(response, clientAddress))
                    {
                        std::cerr << "Failed to send room address to client." << std::endl;
                    }
                    else
                    {
                        std::cout << "Sent room address to client: " << roomAddress << std::endl;
                    }
                }
            }
        }
    }

    bool Room::sendMessage(const std::string &message)
    {
        ssize_t sent = sendto(_sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&_addr, sizeof(_addr));
        return sent >= 0;
    }

    void Room::start(int port)
    {
        if (!_udpServer.initialize("rtype_game/config/udp_config.conf", port))
        {
            std::cerr << "Failed to initialize socket for room " << _name << std::endl;
            return;
        }

        // Lancer le thread pour écouter les messages
        _listenThread = std::thread(&Room::listenForMessages, this);
        _listenThread.detach(); // Laisser le thread détaché pour tourner en arrière-plan
    }

    void Room::createClient(std::string lastclientAdr)
    {
        // Simuler la création du client

        std::cout << "Client created in room [" << _name << "] with addr: " << lastclientAdr << std::endl;

        std::string roomAddress = getAddress(); // Récupérer l'adresse sous forme "IP:port"

        // Créer le message de bienvenue avec l'adresse de la room
        std::string message = "Welcome to the room, client! The room address is: " + roomAddress;

        // Envoyer le message au client
        _udpServer.sendMessage(message, lastclientAdr);
    }

    void Room::closeRoom()
    {
        if (_sockfd >= 0)
        {
            close(_sockfd);
            _sockfd = -1;
        }
    }

    std::string Room::getName() const
    {
        return _name;
    }

    std::string Room::getAddress() const
    {
        // Convertir l'adresse IP en chaîne
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(this->_addr.sin_addr), ipStr, INET_ADDRSTRLEN);
        // Retourner l'adresse sous forme "IP:port"
        return std::string(ipStr) + ":" + std::to_string(ntohs(this->_addr.sin_port));
    }

}
