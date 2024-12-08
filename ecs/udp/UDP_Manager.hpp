/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
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
        {
        public:
            UDP_Manager();
            ~UDP_Manager();

            virtual bool initialize(const std::string &configFile, int port = 0);
            virtual void startReceiving();
            virtual void stopReceiving();

            virtual std::vector<std::pair<std::string, std::vector<char>>> fetchAllMessages();
            virtual bool sendMessage(const std::vector<char> &message, const std::string &address);

            virtual std::string getLastClientAddress() const;

        protected:
            int sockfd;
            int bufferSize;
            sockaddr_in serverAddr;
            sockaddr_in lastSenderAddr;
            bool lastSenderValid;
            std::string clientAddrStr;

            // Gestion des messages
            std::queue<std::pair<std::string, std::vector<char>>> messageQueue;
            std::mutex queueMutex;
            std::condition_variable queueCondition;

            // Gestion du thread
            std::atomic<bool> isRunning;
            std::thread receiverThread;

            virtual void receiveLoop();
            bool receiveMessage(std::vector<char> &message);
            void enqueueMessage(const std::vector<char> &message, const std::string &clientAddress);
        };
        }
    }

#endif // UDP_MANAGER_HPP