/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "Client.hpp"

// int main()
// {
//     rtype::Client RTYPE_CLIENT;

//     try
//     {
//         RTYPE_CLIENT.start();
//     }
//     catch (std::exception &e)
//     {
//         std::cerr << std::endl
//                   << e.what() << std::endl;
//         exit(84);
//     }
// }

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

int main() {
    ecs::udp::UDP_Client client;

    try {
        // Initialize client with configuration file and port
        if (!client.initialize("rtype_game/config/udp_config.conf")) {
            std::cerr << "[ERROR] Failed to initialize client!" << std::endl;
            return 1;
        }

        client.setDefaultAddress("10.109.251.210:8080");

        std::cout << "[INFO] Client is ready to send messages to server." << std::endl;

        for (int i = 0; i < 5; ++i) {
            std::string message = "Hello, Server! Message #" + std::to_string(i);
            std::vector<char> data(message.begin(), message.end());

            if (client.sendMessageToDefault(data)) {
                std::cout << "[SENT] " << message << std::endl;
            } else {
                std::cerr << "[ERROR] Failed to send message to server." << std::endl;
            }

            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
