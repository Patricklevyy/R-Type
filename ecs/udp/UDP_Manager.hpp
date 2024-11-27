/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

#ifndef UDP_MANAGER_HPP
    #define UDP_MANAGER_HPP

    #include <iostream>
    #include <string>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <libconfig.h++>

    class UDP_Manager {
        public:
            UDP_Manager();
            virtual ~UDP_Manager();

            virtual bool initialize(const std::string& configFile, int port = 0);
            virtual bool sendMessage(const std::string& message, const std::string &address);
            virtual bool receiveMessage(std::string& message);
            virtual bool respond(const std::string& message);
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