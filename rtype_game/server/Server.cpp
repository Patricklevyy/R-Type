/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include "../../ECS/UDP_Manager.hpp"

rtype::Server::Server()
{
    std::cout << "START OF THE RTYPE SERVER" << std::endl;
}

rtype::Server::~Server()
{
    std::cout << "STOP OF THE RTYPE SERVER" << std::endl;
}

bool rtype::Server::isRunning() const
{
    return this->_running;
}

void rtype::Server::setRunning(bool running)
{
    this->_running = running;
}

int rtype::Server::start()
{
    UDP_Manager udpManager;

    if (!udpManager.initialize("rtype_game/config/udp_config.conf", true)) {
        std::cerr << "Server initialization failed." << std::endl;
        return 1;
    }

    std::string message;
    while (isRunning()) {

        if (udpManager.receiveMessage(message)) {
            std::cout << "Received message: " << message << std::endl;

            if (!udpManager.respond("Server received: tg sale pute" + message)) {
                std::cerr << "Failed to send response." << std::endl;
            }
        }
    }
    return 0;

}