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

                // void addRoom(const sockaddr_in& roomAddr) {
                //     Room newRoom(roomAddr);
                //     newRoom.start();
                //     rooms.push_back(std::move(newRoom));
                // }

                // void stop() {
                //     for (auto& room : rooms) {
                //         room.stop();
                //     }
                // }

                bool isRunning() const;
                void setRunning(bool);

            private:
                bool _running = true;
                // std::vector<Room> rooms;
            };
    }


#endif /* !SERVER_HPP_ */
