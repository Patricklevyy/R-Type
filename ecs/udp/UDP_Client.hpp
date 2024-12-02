/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Client
*/

#ifndef UDP_CLIENT_HPP_
    #define UDP_CLIENT_HPP_

    #include "UDP_Manager.hpp"

    namespace ecs
    {
        namespace udp
        {
            class UDP_Client : public UDP_Manager{
                public:
                    UDP_Client();
                    ~UDP_Client();

                    bool initialize(const std::string &configFile, int port = 0) override;

                protected:
                private:
            };
        }
    }

#endif /* !UDP_CLIENT_HPP_ */
