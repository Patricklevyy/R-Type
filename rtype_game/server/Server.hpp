/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "Room.hpp"
    #include <vector>
    #include <iostream>

    namespace rtype
    {
        class Server {
            public:
                Server();
                ~Server();

                int start();

                bool isRunning() const;
                void setRunning(bool);

            private:
                bool _running;
                std::vector<Room> _rooms;
                int _currentPort;
                UDP_Manager udpManager;

                void createRoom(const std::string& name);
                void notifyRoomToCreateClient(const std::string& roomName, std::string lastclientAdr);
            };
    }


#endif /* !SERVER_HPP_ */
