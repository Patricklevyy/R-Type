/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "Server.hpp"

// int main()
// {
//     rtype::Server RYTPE_SERVER;

//     try
//     {
//         RYTPE_SERVER.start();
//     }
//     catch (std::exception &e)
//     {
//         std::cerr << std::endl << e.what() << std::endl;
//         exit(84);
//     }
// }

#include <iostream>

int main() {
    ecs::udp::UDP_Manager server;

    try {
        // Initialize server with configuration file and port
        if (!server.initialize("rtype_game/config/udp_config.conf")) {
            std::cerr << "[ERROR] Failed to initialize server!" << std::endl;
            return 1;
        }

        // Start receiving messages
        server.startReceiving();
        std::cout << "[INFO] Server is running and listening on port 8080." << std::endl;

        while (true) {
            auto messages = server.fetchAllMessages();

            for (const auto& [clientAddr, message] : messages) {
                std::string receivedMessage(message.begin(), message.end());
                std::cout << "[RECEIVED] From " << clientAddr << ": " << receivedMessage << std::endl;

                // Echo back to the client
                std::vector<char> response = {'E', 'C', 'H', 'O', ':', ' '};
                response.insert(response.end(), message.begin(), message.end());
                server.sendMessage(response, clientAddr);
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        server.stopReceiving();
    } catch (const std::exception& e) {
        std::cerr << "[ERROR] Exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
