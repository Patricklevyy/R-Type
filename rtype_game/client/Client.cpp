/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"
#include "../../ecs/components/Direction.hpp"

namespace rtype
{
    Client::Client()
    {
        _udpClient = std::make_shared<ecs::udp::UDP_Client>();
        _timer = std::make_shared<Timer>();
    }

    Client::~Client()
    {
        _udpClient->stopReceiving();
    }

    void Client::init_ecs_client_registry()
    {
        _ecs.addRegistry<Window>();
        _ecs.addRegistry<Displayable>();
        _ecs.addRegistry<Health>();
    }

    void Client::init_subscribe_event_bus()
    {
        _eventBus.subscribe(RTYPE_ACTIONS::GET_WINDOW_EVENT, [this](const std::vector<std::any> &args) {
            (void)args;
            _events = _event_window_system.fetchEvents();
        });
        _eventBus.subscribe(RTYPE_ACTIONS::START_LISTEN_EVENT, [this](const std::vector<std::any> &args) {
            (void)args;
            _event_window_system.startListening(_ecs._components_arrays);
        });
         _eventBus.subscribe(RTYPE_ACTIONS::STOP_LISTEN_EVENT, [this](const std::vector<std::any> &args) {
            (void)args;
            _event_window_system.stopListening();
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, [this](const std::vector<std::any> &args) {
            try {
                std::tuple<ecs::direction, ecs::direction, size_t> _x_y_index = std::any_cast<std::reference_wrapper<std::tuple<ecs::direction, ecs::direction, size_t>>>(args[0]).get();
                _direction_system.updatePlayerDirection(_ecs._components_arrays, std::get<0>(_x_y_index), std::get<1>(_x_y_index), std::get<2>(_x_y_index));
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
         _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_PLAYER_POSITION, [this](const std::vector<std::any> &args) {
            (void)args;
            _position_system.updatePlayerPositions(_ecs._components_arrays, _timer->getTps(), _ecs.getIndexPlayer());
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [this](const std::vector<std::any> &args) {
            try {
                auto& message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                std::list<std::tuple<std::size_t, std::pair<float, float>, int>> entities = Command_checker::parse_update(message.params);

                while (!entities.empty()) {
                    auto it = ecs_server_to_client.find(std::get<0>(entities.front()));
                    std::cout << _ecs.getIndexPlayer() << " , " << ecs_server_to_client[std::get<0>(entities.front())] << std::endl;
                    if (it != ecs_server_to_client.end() && _ecs.getIndexPlayer() != ecs_server_to_client[std::get<0>(entities.front())]) {
                        _update_entity_system.updateEntity(_ecs._components_arrays, entities.front(), ecs_server_to_client[std::get<0>(entities.front())]);
                    }
                    entities.pop_front();
                }
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: UPDATE POSSSS" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::CREATE_TEAMMATE, [this](const std::vector<std::any> &args) {
            try {
                auto& message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                size_t separator_pos = message.params.find(';');

                std::string x_part = message.params.substr(0, separator_pos);
                std::string y_part = message.params.substr(separator_pos + 1);

                float x = std::stof(x_part.substr(2));
                float y = std::stof(y_part.substr(2));

                createEntity(message.id, x, y, SPRITES::SHIP);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::RENDER_WINDOW, [this](const std::vector<std::any>& args) {
            (void)args;
            _render_window_system.render(_ecs._components_arrays);
        });
    }

    void Client::createEntity(unsigned int server_id, float x, float y, int sprite_id)
    {
        ecs::Position position(x, y);
        Displayable displayable(sprite_id, x ,y);
        Health health;

        _ecs.addComponents<ecs::Position>(_index_ecs_client, position);
        _ecs.addComponents<Health>(_index_ecs_client, health);
        _ecs.addComponents<Displayable>(_index_ecs_client, displayable);

        ecs_server_to_client[server_id] = _index_ecs_client;
        ecs_client_to_server[_index_ecs_client] = server_id;

        _index_ecs_client++;
    }

    void Client::setRoomAdress(unsigned int server_id, std::map<std::string, std::string> params)
    {
        std::string ip_port = Command_checker::check_adress(params, _udpClient->getServerIp());
        _udpClient->setDefaultAddress(ip_port);
    }

    void Client::createPlayer(unsigned int server_id, std::map<std::string, std::string> params)
    {
        float x = std::stof(params["x"]);
        float y = std::stof(params["y"]);

        ecs::Direction direction;
        ecs::Playable playable(_name);
        ecs::Position position(x, y);
        ecs::Velocity velocity;
        Displayable displayable(1, x ,y);
        Health health;

        _ecs.addComponents<ecs::Direction>(_index_ecs_client, direction);
        _ecs.addComponents<ecs::Playable>(_index_ecs_client, playable);
        _ecs.addComponents<ecs::Velocity>(_index_ecs_client, velocity);
        _ecs.addComponents<ecs::Position>(_index_ecs_client, position);
        _ecs.addComponents<Displayable>(_index_ecs_client, displayable);
        _ecs.addComponents<Health>(_index_ecs_client, health);

        ecs_server_to_client[server_id] = _index_ecs_client;
        ecs_client_to_server[_index_ecs_client] = server_id;

        _index_ecs_client++;
    }

    void Client::handle_message(std::vector<char>& message, std::string clientAddr)
    {
        ecs::udp::Message mes;
        _message_compressor.deserialize(message, mes);
        _mes_checker.checkAction(mes);
        std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << " body " << mes.body << std::endl;
        std::map<std::string, std::string> params = _mes_checker.checkFormatParams(mes.params);
        unsigned int id = mes.id;
        rtype::RTYPE_ACTIONS action = static_cast<rtype::RTYPE_ACTIONS>(mes.action);
        if (action == RTYPE_ACTIONS::CREATE_CLIENT) {
            setRoomAdress(id, params);
            createPlayer(id, params);
            _in_menu = false;
            return;
        }
        _eventBus.emit(action, std::ref(mes));
    }

    void Client::send_server_player_direction(ecs::direction x, ecs::direction y)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = ecs_client_to_server[_ecs.getIndexPlayer()];;
        mess.action = RTYPE_ACTIONS::UPDATE_DIRECTION;
        mess.params = "x=" + std::to_string(x) + ";y=" + std::to_string(y);

        _message_compressor.serialize(mess, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::handle_event()
    {
        while (!_events.empty())
        {
            std::cout << "SIZE : " << _events.size() << std::endl;
            sf::Event event = _events.front();
            _events.pop();
            switch (event.type) {
                case sf::Event::Closed:
                    // DIRE A LA ROOM QUE LE CLIENT SE DECONNECTE
                    _running = false;
                    return;

                case sf::Event::KeyPressed:
                    std::cout << "KEYH PRESSED" << std::endl;
                    if (event.key.code == sf::Keyboard::Escape) {
                        _running = false;
                        return;
                    }
                    if (event.key.code == sf::Keyboard::D && !_in_menu) {
                        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(ecs::direction::RIGHT, ecs::direction::NO_CHANGE, _ecs.getIndexPlayer());
                        send_server_player_direction(ecs::direction::RIGHT, ecs::direction::NO_CHANGE);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::Q && !_in_menu) {
                        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(ecs::direction::LEFT, ecs::direction::NO_CHANGE, _ecs.getIndexPlayer());
                        send_server_player_direction(ecs::direction::LEFT, ecs::direction::NO_CHANGE);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::Z && !_in_menu) {
                        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(ecs::direction::NO_CHANGE, ecs::direction::UP, _ecs.getIndexPlayer());
                        send_server_player_direction(ecs::direction::NO_CHANGE, ecs::direction::UP);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::S && !_in_menu) {
                        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(ecs::direction::NO_CHANGE, ecs::direction::DOWN, _ecs.getIndexPlayer());
                        send_server_player_direction(ecs::direction::NO_CHANGE, ecs::direction::DOWN);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::A) {
                        std::vector<char> buffer;
                        ecs::udp::Message mess;
                        mess.id = 1;
                        mess.action = 0;
                        mess.params = "room_name=room1;client_name=jean";

                        _message_compressor.serialize(mess, buffer);

                        std::cout << "je send" << std::endl;
                        if (_udpClient->sendMessageToDefault(buffer)) {
                            std::cout << "Message sent: " << std::endl;
                        } else {
                            std::cout << "failed " << std::endl;
                        }
                    }
                    if (event.key.code == sf::Keyboard::B) {
                        std::vector<char> buffer;
                        ecs::udp::Message mess;
                        mess.id = 1;
                        mess.action = 1;
                        mess.params = "room_name=room1;client_name=patrick";

                        _message_compressor.serialize(mess, buffer);

                        std::cout << "je send" << std::endl;
                        if (_udpClient->sendMessageToDefault(buffer)) {
                            std::cout << "Message sent: " << std::endl;
                        } else {
                            std::cout << "failed " << std::endl;
                        }
                    }
                    break;
                case sf::Event::KeyReleased:
                    if ((event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Q) && !_in_menu) {
                        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE, _ecs.getIndexPlayer());
                        send_server_player_direction(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
                    }
                    if ((event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S) && !_in_menu) {
                        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION, _ecs.getIndexPlayer());
                        send_server_player_direction(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
                    }
                    break;

                default:
                    std::cout << "Événement non traité." << std::endl;
                    break;
            }
        }
    }

    void Client::init_window_and_background()
    {
        Window window(800, 800, "R-Type");
        _ecs.addComponents<Window>(_index_ecs_client, window);
        _ecs.addComponents<Displayable>(_index_ecs_client, Displayable(SPRITES::BACKGROUND, 0, 0));
        _ecs.addComponents<ecs::Position>(_index_ecs_client, ecs::Position(0, 0));
        _index_ecs_client++;
    }

    void Client::init_all()
    {
        if (!_udpClient->initialize("rtype_game/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeClientExceptions("Failed to initialize client");
        }
        _timer->init("rtype_game/config/client_config.conf", false);
        _udpClient->startReceiving();
        _ecs.init_basic_registry();
        init_ecs_client_registry();
        init_window_and_background();
        init_subscribe_event_bus();
        _eventBus.emit(RTYPE_ACTIONS::START_LISTEN_EVENT);
    }

    void Client::start()
    {
        init_all();

        while (_running) {
            _timer->waitTPS();
            _eventBus.emit(RTYPE_ACTIONS::GET_WINDOW_EVENT);
            handle_event();
            _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_POSITION);
            auto messages = _udpClient->fetchAllMessages();
            for (auto &[clientAddress, message] : messages) {
                try {
                    handle_message(message, clientAddress);
                } catch (std::exception &e) {
                    std::cerr << std::endl << e.what() << std::endl;
                }
            }
            _ecs.displayPlayableEntityComponents();
            _eventBus.emit(RTYPE_ACTIONS::RENDER_WINDOW);
        }
        _eventBus.emit(RTYPE_ACTIONS::STOP_LISTEN_EVENT);
    }
}
