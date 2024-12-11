/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Client
*/

/**
 * @file UDP_Client.hpp
 * @brief Manages the client-side communication via UDP protocol.
 */

#ifndef UDP_CLIENT_HPP_
    #define UDP_CLIENT_HPP_

    #include "UDP_Manager.hpp"

    namespace ecs
    {
        namespace udp
        /**
         * @class UDP_Client
         * @brief Implements a non-blocking UDP client for sending and receiving messages.
         */
        {
            class UDP_Client : public UDP_Manager
            {
            public:
                /**
                 * @brief Default constructor for the UDP_Client.
                 */
                UDP_Client();

                /**
                 * @brief Default destructor for the UDP_Client.
                 */
                ~UDP_Client();

                /**
                 * @brief Initializes the client using configuration settings from a file.
                 * @param configFile The path to the configuration file.
                 * @param port The optional port to bind the client to (default is 0).
                 * @return True if initialization succeeds, false otherwise.
                 */
                bool initialize(const std::string &configFile, int port = 0) override;

                /**
                 * @brief Sets the default address for message transmission.
                 * @param address The default address to send messages to.
                 */
                void setDefaultAddress(const std::string &);

                /**
                 * @brief Sends a message to the pre-configured default address.
                 * @param message The message to send as a vector of bytes.
                 * @return True if the message is successfully sent, false otherwise.
                 */
                bool sendMessageToDefault(const std::vector<char>);

            protected:
                std::string defaultAddress; /**< The default address for message transmission. */
            private:
            };
        }
    }

#endif /* !UDP_CLIENT_HPP_ */
