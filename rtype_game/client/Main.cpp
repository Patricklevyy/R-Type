/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "../../ECS/UDP_Manager.hpp"
#include <iostream>

int main() {
    UDP_Manager udpManager;

    if (!udpManager.initialize("rtype_game/config/udp_config.conf", false)) {
        std::cerr << "Client initialization failed." << std::endl;
        return 1;
    }

    std::string message = "CREATE";

    if (udpManager.sendMessage(message)) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message." << std::endl;
        return 1;
    }

    std::string response;
    if (udpManager.receiveMessage(response)) {
        std::cout << "Received response: " << response << std::endl;
    } else {
        std::cerr << "Failed to receive response." << std::endl;
        return 1;
    }

    return 0;
}
