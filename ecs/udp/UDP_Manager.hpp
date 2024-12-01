/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

#ifndef UDP_MANAGER_HPP
    #define UDP_MANAGER_HPP

    #include "../Includes.hpp"

    class UDP_Manager {
        public:
            UDP_Manager();
            virtual ~UDP_Manager();

            virtual bool initialize(const std::string& configFile, int port = 0);
            virtual bool sendMessage(const std::vector<char>& message, const std::string &address);
            virtual bool receiveMessage(std::vector<char>& message);
            virtual std::string getLastClientAddress() const;

        protected:
            int sockfd;
            int bufferSize;
            sockaddr_in serverAddr;
            sockaddr_in lastSenderAddr;
            bool lastSenderValid;
            std::string clientAddrStr;
        };

#endif // UDP_MANAGER_HPP