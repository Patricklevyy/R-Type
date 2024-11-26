/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include "../../ecs/udp/UDP_Manager.hpp"

namespace rtype {

    Server::Server() : _running(true), _currentPort(5000)
    {
        std::cout << "START OF THE RTYPE SERVER" << std::endl;
    }

    Server::~Server()
    {
        std::cout << "STOP OF THE RTYPE SERVER" << std::endl;
    }

    bool Server::isRunning() const
    {
        return this->_running;
    }

    void Server::setRunning(bool running)
    {
        this->_running = running;
    }

    int Server::start()
    {
        if (!udpManager.initialize("rtype_game/config/udp_config.conf")) {
            std::cerr << "Server initialization failed." << std::endl;
            return 1;
        }

        std::string message;
        while (isRunning()) {
       
            if (udpManager.receiveMessage(message)) {
                std::cout << "Received message: " << message << std::endl;

                // Si le message est "CREATE", on crée une room
                if (message.compare("CREATE") == 0) {
                    std::cout << "Creating room" << std::endl;
                    createRoom("room1");

                    // Notifier la room pour qu'elle crée un client (par exemple)
                    notifyRoomToCreateClient("room1", udpManager.getLastClientAddress());
                }
            }
        }
        return 0;
    }

    void Server::notifyRoomToCreateClient(const std::string& roomName, std::string lastclientAdr)
    {
        // Vous pouvez parcourir les rooms et trouver celle qui correspond au nom
        for (auto& room : _rooms) {
            if (room.getName() == roomName) {
                room.createClient(lastclientAdr);  // Appeler une méthode de la room pour créer un client
            }
        }
    }

    void Server::createRoom(const std::string& name) {
        Room newRoom(_currentPort, name);
        _rooms.push_back(std::move(newRoom));  // Déplacer l'objet dans le vector

        // Lancer la room, elle gère son propre thread
        _rooms.back().start(_currentPort);
        _currentPort++;  // Incrémenter le port pour la prochaine room
    }
}