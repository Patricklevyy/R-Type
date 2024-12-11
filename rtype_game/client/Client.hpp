/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    #include "../shared/Includes.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Client.hpp"
    #include "../../ecs/Structures_ecs.hpp"
    #include "../../ecs/ECS.hpp"
    #include "../shared/EventBus.hpp"
    #include "components/Window.hpp"
    #include "system/EventWindow.hpp"
    #include "../shared/Timer.hpp"
    #include "../shared/MessageChecker.hpp"
    #include "Command_checker.hpp"
    #include "../shared/system/DirectionSystem.hpp"
    #include "../../ecs/system/PositionSystem.hpp"

    namespace rtype
    {
        class Client
        {
            public:
                Client();
                ~Client();

                void start();

                void init_ecs_client_registry();
                void init_subscribe_event_bus();

                void handle_event();
                void handle_message(std::vector<char>&, std::string);

            protected:
            private:
                bool _in_menu = true;
                std::string _name; // A SET AU MENU
                std::map<unsigned int, unsigned int> ecs_server_to_client;
                std::map<unsigned int, unsigned int> ecs_client_to_server;
                EventBus _eventBus;
                std::shared_ptr<Timer> _timer;
                std::shared_ptr<ecs::udp::UDP_Client> _udpClient;
                ecs::ECS _ecs;
                bool _running = true;
                std::queue<sf::Event> _events;
                ecs::udp::MessageCompressor _message_compressor;
                MessageChecker _mes_checker;
                size_t _index_ecs_client = 0;

                // SYSTEMS

                EventWindow _event_window_system;
                DirectionSystem _direction_system;
                ecs::PositionSystem _position_system;

                void setRoomAdress(unsigned int, std::map<std::string, std::string>);
                void createPlayer(unsigned int, std::map<std::string, std::string>);
                void send_server_player_direction(ecs::direction, ecs::direction);
        };
    }
#endif /* !CLIENT_HPP_ */
