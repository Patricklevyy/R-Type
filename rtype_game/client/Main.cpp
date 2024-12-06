/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "../../ecs/udp/UDP_Client.hpp"
#include <iostream>
#include <cstring>
#include "../../ecs/Structures_ecs.hpp"
#include "../../ecs/udp/MessageCompressor.hpp"

int main() {
    ecs::udp::UDP_Client udpClient;

    if (!udpClient.initialize("rtype_game/config/udp_config.conf")) {
        std::cerr << "Client initialization failed." << std::endl;
        return 1;
    }

    std::string message = "CREATE";

    std::vector<char> buffer;
    ecs::udp::Message mess;
    mess.id = 1;
    mess.action = 1;
    mess.params = "room_name=room1;client_name=jean";

    ecs::udp::MessageCompressor compresor;

    compresor.serialize(mess, buffer);

    if (udpClient.sendMessage(buffer, "127.0.0.1:8080")) {
        std::cout << "Message sent: " << message << std::endl;
    } else {
        std::cerr << "Failed to send message." << std::endl;
        return 1;
    }

    // std::cout << "Waiting for response from the server..." << std::endl;

    // std::string response;
    // bool messageReceived = false;
    // std::string roomAddress;

    // for (int i = 0; i < 10; ++i) {
    //     if (udpClient.receiveMessage(response)) {
    //         std::cout << "Received response: " << response << std::endl;

    //         if (response.find("The room address is:") != std::string::npos) {
    //             size_t pos = response.find("The room address is:") + std::strlen("The room address is: ");
    //             roomAddress = response.substr(pos);
    //             std::cout << "Room address received: " << roomAddress << std::endl;

    //             if (udpClient.sendMessage("Received room address: " + roomAddress, "127.0.0.1:8080")) {
    //                 std::cout << "Message with room address sent to server." << std::endl;
    //             } else {
    //                 std::cerr << "Failed to send room address back to the server." << std::endl;
    //             }
    //         }
    //         messageReceived = true;
    //         break;
    //     } else {
    //         std::cerr << "Failed to receive response. Retrying..." << std::endl;
    //         usleep(500000);
    //     }
    // }

    // if (!messageReceived) {
    //     std::cerr << "Server not available or no response received after several retries." << std::endl;
    // }

    return 0;
}

