/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

#ifndef ROOM_HPP_
    #define ROOM_HPP_

    #include "../shared/Includes.hpp"
    #include "MessageChecker.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Server.hpp"
    #include "../../ecs/ECS.hpp"
    #include "../../ecs/Includes_ecs.hpp"
    #include "../../ecs/system/PositionSystem.hpp"
    #include "../shared/EventBus.hpp"
    #include "../shared/Timer.hpp"

    namespace rtype
    {
        class Room
        {
        public:
            Room(int port, const std::string &name);
            ~Room();

            void start(int port);

            void gameThreadFunction(int);

            bool sendMessage(const std::string &message);

            unsigned int getNbClient() const;
            void setNbClient(unsigned int);

            Room(const Room &) = delete;
            Room(Room &&other) noexcept;
            Room &operator=(const Room &) = delete;
            Room &operator=(Room &&other) noexcept;

            std::string getName() const;
            void createClient(std::string lastclientAdr);
            std::string getAddress() const;

            void init_event_bus();


        private:
            unsigned int index_ecs = 0;
            ecs::udp::UDP_Server _udp_server;
            ecs::udp::MessageCompressor _message_compressor;
            bool _game_running;
            ecs::ECS _ecs;
            EventBus _eventBus;
            int _port;
            std::string _name;
            unsigned int _nb_client;
            int _sockfd;
            struct sockaddr_in _addr;
            std::thread _gameThread;

            bool initializeSocket();
            void closeRoom();
            void init_ecs_server_registry();
            void handleCommand(const std::vector<char> &, std::string clientAddr);
        };
    }

#endif /* !ROOM_HPP_ */
