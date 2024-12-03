/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

#ifndef ROOM_HPP_
    #define ROOM_HPP_

    #include "Includes.hpp"
    #include "MessageChecker.hpp"
    #include "../../ecs/udp/UDP_Server.hpp"

    namespace rtype {
        class Room {
            public:
                Room(int port, const std::string& name);
                ~Room();

                void start(int port);

                void listenForMessages();

                bool sendMessage(const std::string& message);

                unsigned int getNbClient() const;
                void setNbClient(unsigned int);

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
                unsigned int _nb_client;
                int _sockfd;
                struct sockaddr_in _addr;
                ecs::udp::UDP_Server _udpServer;
                std::thread _listenThread;

                bool initializeSocket();

                void closeRoom();
        };
    }

#endif /* !ROOM_HPP_ */
