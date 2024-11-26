/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "../../ecs/udp/UDP_Client.hpp"
#include <iostream>
#include <cstring>

int main() {
    UDP_Client udpClient;
    
    if (!udpClient.initialize("rtype_game/config/udp_config.conf")) {
        std::cerr << "Client initialization failed." << std::endl;
        return 1;
    }

    std::string message = "CREATE";

    // Envoyer le message "CREATE" au serveur
    if (udpClient.sendMessage(message, "127.0.0.1:8080")) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message." << std::endl;
        return 1;
    }

    // Attendre une réponse du serveur
    std::cout << "Waiting for response from the server..." << std::endl;

    std::string response;
    bool messageReceived = false;
    std::string roomAddress;  // Pour stocker l'adresse de la room

    // Essayer de recevoir une réponse du serveur
    for (int i = 0; i < 10; ++i) {  // Essayer jusqu'à 10 fois
        if (udpClient.receiveMessage(response)) {
            std::cout << "Received response: " << response << std::endl;

            // Extraire l'adresse de la room de la réponse, si elle est incluse
            if (response.find("The room address is:") != std::string::npos) {
                size_t pos = response.find("The room address is:") + std::strlen("The room address is: ");
                roomAddress = response.substr(pos);
                std::cout << "Room address received: " << roomAddress << std::endl;

                // Renvoyer l'adresse de la room au serveur
                if (udpClient.sendMessage("Received room address: " + roomAddress, "127.0.0.1:8080")) {
                    std::cout << "Message with room address sent to server." << std::endl;
                } else {
                    std::cerr << "Failed to send room address back to the server." << std::endl;
                }
            }
            messageReceived = true;
            break;  // Quitter la boucle si une réponse est reçue
        } else {
            std::cerr << "Failed to receive response. Retrying..." << std::endl;
            usleep(500000);  // Attendre 500ms avant de réessayer
        }
    }

    // Si aucune réponse n'est reçue après plusieurs essais, afficher un message d'erreur
    if (!messageReceived) {
        std::cerr << "Server not available or no response received after several retries." << std::endl;
    }

    return 0;
}


// if (isServer) {
//             const libconfig::Setting &serverSettings = udpSettings["server"];
//             std::string ip = serverSettings["ip"];
//             int port = serverSettings["port"];
//             addr.sin_port = htons(port);
//             inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

//             sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//             if (sockfd < 0)
//             {
//                 perror("Socket creation failed"); // TODO : REMPLACER PAR DES EXCEPTIONS
//                 return false;
//             }

//             if (bind(sockfd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
//                 perror("Bind failed"); // TODO : REMPLACER PAR DES EXCEPTIONS
//                 close(sockfd);
//                 sockfd = -1;
//                 return false;
//             }

//             std::cout << "Server is running on " << ip << ":" << port << "\n";
//         } else {
//             const libconfig::Setting &clientSettings = udpSettings["client"];
//             std::string ip = clientSettings["ip"];
//             int port = clientSettings["port"];
//             addr.sin_port = htons(port);
//             inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

//             const libconfig::Setting &serverSettings = udpSettings["server"];
//             std::string serverIp = serverSettings["ip"];
//             int serverPort = serverSettings["port"];
//             serverAddr.sin_family = AF_INET;
//             serverAddr.sin_port = htons(serverPort);
//             inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr);

//             sockfd = socket(AF_INET, SOCK_DGRAM, 0);
//             if (sockfd < 0)
//             {
//                 perror("Socket creation failed"); // TODO : REMPLACER PAR DES EXCEPTIONS
//                 return false;
//             }

//             std::cout << "Client initialized to connect to " << serverIp << ":" << serverPort << "\n";
//         }