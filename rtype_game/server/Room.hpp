/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

#ifndef ROOM_HPP_
    #define ROOM_HPP_

    #include <string>
    #include <thread>
    #include <iostream>
    #include <unistd.h>  // Pour close() et autres appels liés aux sockets
    #include <netinet/in.h>  // Pour sockaddr_in
    #include "../../ecs/udp/UDP_Server.hpp"

    namespace rtype {
        class Room {
            public:
                Room(int port, const std::string& name);
                ~Room();

                void start(int port);

                void listenForMessages();

                bool sendMessage(const std::string& message);

                Room(const Room&) = delete;
                Room(Room&& other) noexcept;
                Room& operator=(const Room&) = delete;
                Room& operator=(Room&& other) noexcept;

                std::string getName() const;
                void createClient(std::string lastclientAdr);
                std::string getAddress() const;

            private:
                int _port;
                std::string _name;
                int _sockfd;
                struct sockaddr_in _addr;
                UDP_Server _udpServer;
                std::thread _listenThread;

                bool initializeSocket();

                void closeRoom();
        };
    }

#endif /* !ROOM_HPP_ */
