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
                EventBus _eventBus;
                std::shared_ptr<Timer> _timer;
                std::shared_ptr<ecs::udp::UDP_Client> _udpClient;
                ecs::ECS _ecs;
                bool _running = true;
                std::queue<sf::Event> _events;
                ecs::udp::MessageCompressor _message_compressor;
                MessageChecker _mes_checker;

        };
    }
#endif /* !CLIENT_HPP_ */
