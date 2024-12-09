/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Server
*/

#ifndef UDP_SERVER_HPP
    #define UDP_SERVER_HPP

    #include "UDP_Manager.hpp"

    namespace ecs
    {
        namespace udp
        {
            class UDP_Server : public UDP_Manager
            {
            public:
                UDP_Server();
                ~UDP_Server();

                bool initialize(const std::string &configFile, int port = 0) override;

            private:
            };
        }
    }

#endif // UDP_SERVER_HPP"