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
    #include "components/Background.hpp"
    #include "components/Sprite.hpp"
    #include "system/RenderWindow.hpp"
    #include "../shared/components/Health.hpp"
    #include "system/UpdateEntitySystem.hpp"
    #include "components/Displayable.hpp"
    #include "../shared/MessageChecker.hpp"
    #include "../shared/Enums.hpp"
    namespace rtype
    {
        class Client
        {
            public:
                Client();
                ~Client();

                void start();

                void handle_event();
                void handle_message(std::vector<char>&, std::string);
                void requestAvailableRooms();

            protected:
            private:
                int _window_width;
                int _window_height;
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
                RenderWindow _render_window_system;
                UpdateEntitySystem _update_entity_system;

                void killEntity(std::list<size_t>);

                void setRoomAdress(unsigned int, int);
                void createPlayer(unsigned int, float, float);
                void init_game(ecs::udp::Message &);
                void createEntity(unsigned int, float, float, SPRITES);
                void createProjectile(ecs::udp::Message&);
                void updateEntitiesFirstConnexion(const std::string &);

                void createMonster(ecs::udp::Message&);

                // MESSAGE TO SERVER

                void send_server_new_shoot();
                void send_server_player_direction(ecs::direction, ecs::direction);
                void send_server_start_game();

                // INITIALISATION

                void init_all();
                void init_window_size(const std::string&);
                void init_window_and_background();
                void init_ecs_client_registry();
                void init_subscribe_event_bus();
        };
    }
#endif /* !CLIENT_HPP_ */
