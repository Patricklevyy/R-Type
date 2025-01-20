/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

/**
 * @file UDP_Manager.hpp
 * @brief Base class to manage UDP socket communication, including message reception and transmission.
 */

#ifndef UDP_MANAGER_HPP
    #define UDP_MANAGER_HPP

    #include "../Includes_ecs.hpp"
    #include "../EcsExceptions.hpp"

    namespace ecs
    {
        namespace udp
        {
            /**
             * @class UDP_Manager
             * @brief Cette UDP manager gère les messages de première connexion d'un client
             *
             */
        class UDP_Manager
        /**
         * @class UDP_Manager
         * @brief Manages the core functionality for sending and receiving messages via UDP.
         * This class provides an interface for derived classes like `UDP_Client` and `UDP_Server`.
         */
        {
        public:
            /**
             * @brief Default constructor for UDP_Manager.
             */
            UDP_Manager();

            /**
             * @brief Default destructor for UDP_Manager.
             */
            ~UDP_Manager();

            /**
             * @brief Initializes the UDP manager with configuration settings.
             * @param configFile Path to the configuration file.
             * @param port The port to bind to (default is 0, which lets the OS select a port).
             * @return True if initialization succeeds, false otherwise.
             */
            virtual bool initialize(const std::string &configFile, int port = 0);

            /**
             * @brief Starts receiving messages on a dedicated thread.
             */
            virtual void startReceiving();

            /**
             * @brief Stops the receiving thread gracefully.
             */
            virtual void stopReceiving();

            /**
             * @brief Fetches all received messages.
             * @return A vector of pairs containing the sender's address and the message.
             */
            virtual std::vector<std::pair<std::string, std::vector<char>>> fetchAllMessages();

            /**
             * @brief Sends a message to a specified address.
             * @param message The message to send as a byte vector.
             * @param address The destination address.
             * @return True if the message is successfully sent, false otherwise.
             */
            virtual bool sendMessage(const std::vector<char> &message, const std::string &address);

            /**
             * @brief Retrieves the address of the last client that sent a message.
             * @return The address as a string.
             */
            virtual std::string getLastClientAddress() const;

            /**
             * @brief Retrieves the secret key for the server.
             * @return The secret key as a string.
             */

            virtual std::string getSecretKey() const;

        protected:
            int sockfd; /**< Socket file descriptor. */
            int bufferSize;  /**< Maximum buffer size for receiving messages. */
            sockaddr_in serverAddr; /**< Server address information. */
            sockaddr_in lastSenderAddr; /**< Address of the last message sender. */
            bool lastSenderValid; /**< Indicates if the last sender address is valid. */
            std::string clientAddrStr;  /**< Cached string representation of the last client address. */
            std::string secret_key;

            // Gestion des messages
            std::queue<std::pair<std::string, std::vector<char>>> messageQueue; /**< Queue for incoming messages. */
            std::mutex queueMutex;  /**< Mutex for synchronizing access to the message queue. */
            std::condition_variable queueCondition; /**< Condition variable for message queue updates. */

            // Gestion du thread
            std::atomic<bool> isRunning; /**< Flag to control the receiving thread. */
            std::thread receiverThread; /**< Thread for receiving messages. */

            /**
             * @brief Main loop for receiving messages.
             */
            virtual void receiveLoop();

            /**
             * @brief Receives a single message from the socket.
             * @param message The buffer to store the received message.
             * @return True if a message is successfully received, false otherwise.
             */
            bool receiveMessage(std::vector<char> &message);

            /**
             * @brief Enqueues a received message into the message queue.
             * @param message The received message as a byte vector.
             * @param clientAddress The address of the sender.
             */
            void enqueueMessage(const std::vector<char> &message, const std::string &clientAddress);
        };
        }
    }

#endif // UDP_MANAGER_HPP