/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Server
*/

/**
 * @file UDP_Server.hpp
 * @brief Extends `UDP_Manager` to implement server-specific functionality for UDP communication.
 */

#ifndef UDP_SERVER_HPP
    #define UDP_SERVER_HPP

    #include "UDP_Manager.hpp"

    namespace ecs
    {
        namespace udp
        {
            /**
             * @class UDP_Server
             * @brief Implements a non-blocking UDP server for receiving and sending messages.
             */
            class UDP_Server : public UDP_Manager
            {
            public:
                /**
                 * @brief Default constructor for UDP_Server.
                 */
                UDP_Server();

                /**
                 * @brief Default destructor for UDP_Server.
                 */
                ~UDP_Server();

                /**
                 * @brief Initializes the server using configuration settings.
                 * @param configFile Path to the configuration file.
                 * @param port The port to bind the server to (default is 0).
                 * @return True if initialization succeeds, false otherwise.
                 */
                bool initialize(const std::string &configFile, int port = 0) override;

            private:
            };
        }
    }

#endif // UDP_SERVER_HPP"