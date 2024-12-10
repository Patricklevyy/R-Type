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

            void start(int, std::string);

            void gameThreadFunction(int, std::string);

            bool sendMessage(const std::string &);

            unsigned int getNbClient() const;
            void setNbClient(unsigned int);

            Room(const Room &) = delete;
            Room(Room &&other) noexcept;
            Room &operator=(const Room &) = delete;
            Room &operator=(Room &&other) noexcept;

            std::string getName() const;
            void createClient(std::string);
            std::string getAddress() const;

            void init_event_bus();


        private:
            int _port;
            unsigned int index_ecs = 0;
            std::shared_ptr<ecs::udp::UDP_Server> _udp_server;
            ecs::udp::MessageCompressor _message_compressor;
            bool _game_running;
            ecs::ECS _ecs;
            EventBus _eventBus;
            std::string _name;
            unsigned int _nb_client;
            int _sockfd;
            struct sockaddr_in _addr;
            std::thread _gameThread;
            ecs::PositionSystem pos;

            bool initializeSocket();
            void closeRoom();
            void init_ecs_server_registry();
            void handleCommand(const std::vector<char> &, std::string clientAddr);
        };
    }

#endif /* !ROOM_HPP_ */
