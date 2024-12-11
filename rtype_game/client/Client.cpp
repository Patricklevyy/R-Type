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
        _ecs.addRegistry<Background>();
    }

    void Client::init_subscribe_event_bus()
    {
        _eventBus.subscribe(RTYPE_ACTIONS::GET_WINDOW_EVENT, [](const std::vector<std::any>& args) {
            try {
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[0]).get();
                auto& event_system = std::any_cast<std::reference_wrapper<EventWindow>>(args[1]).get();
                auto& queue = std::any_cast<std::reference_wrapper<std::queue<sf::Event>>>(args[2]).get();

                queue = event_system.fetchEvents();
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::START_LISTEN_EVENT, [](const std::vector<std::any>& args) {
            try {
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[0]).get();
                auto& event_system = std::any_cast<std::reference_wrapper<EventWindow>>(args[1]).get();

                event_system.startListening(components);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_DIRECTION, [](const std::vector<std::any>& args) {
            try {
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[0]).get();
                auto& direction_system = std::any_cast<std::reference_wrapper<DirectionSystem>>(args[1]).get();
                std::pair<ecs::direction, ecs::direction> _x_y = std::any_cast<std::reference_wrapper<std::pair<ecs::direction, ecs::direction>>>(args[2]).get();

                std::cout << _x_y.first << " , " << _x_y.second << std::endl;
                direction_system.updatePlayerDirection(components, _x_y.first, _x_y.second);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [](const std::vector<std::any>& args) {
            try {
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[0]).get();
                auto& position_system = std::any_cast<std::reference_wrapper<ecs::PositionSystem>>(args[1]).get();
                std::shared_ptr<Timer> timer = std::any_cast<std::shared_ptr<rtype::Timer>>(args[2]);

                position_system.updatePositions(components, timer->getTps());
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::RENDER, [](const std::vector<std::any>& args) {
            try {
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[0]).get();
                auto& EventWindow = std::any_cast<std::reference_wrapper<RenderWindow>>(args[1]).get();

                EventWindow.render(components);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
    }

    void Client::setRoomAdress(unsigned int server_id, std::map<std::string, std::string> params)
    {
        std::string ip_port = Command_checker::check_adress(params);
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

        _ecs.addComponents<ecs::Direction>(_index_ecs_client, direction);
        _ecs.addComponents<ecs::Playable>(_index_ecs_client, playable);
        _ecs.addComponents<ecs::Velocity>(_index_ecs_client, velocity);
        _ecs.addComponents<ecs::Position>(_index_ecs_client, position);

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
            return;
        }
        _eventBus.emit(action, std::ref(id), std::ref(params), _udpClient, std::ref(_index_ecs_client), std::ref(_ecs));
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
                    if (event.key.code == sf::Keyboard::D) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::RIGHT, ecs::direction::NO_CHANGE);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::Q) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::LEFT, ecs::direction::NO_CHANGE);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::Z) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::NO_CHANGE, ecs::direction::UP);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::NO_CHANGE, ecs::direction::DOWN);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
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
                        mess.id = 2;
                        mess.action = 15;
                        // mess.params = "room_name=room1;client_name=jean";

                        _message_compressor.serialize(mess, buffer);

                        std::cout << "je teste GET ALL ROOMS " << std::endl;
                        if (_udpClient->sendMessage(buffer, "127.0.0.1:8080")) {
                            std::cout << "Message sent: " << std::endl;
                        } else {
                            std::cout << "failed " << std::endl;
                        }
                    }
                    break;
                case sf::Event::KeyReleased:
                    if (event.key.code == sf::Keyboard::D) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::Q) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::Z) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        std::pair<ecs::direction, ecs::direction> _x_y(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
                        _eventBus.emit(RTYPE_ACTIONS::UPDATE_DIRECTION, std::ref(_ecs._components_arrays), std::ref(_direction_system), std::ref(_x_y));
                    }
                    break;

                default:
                    std::cout << "Événement non traité." << std::endl;
                    break;
            }
        }
    }

    void Client::init_background()
    {
        Window window(1920, 1080, "R-Type");
        _ecs.addComponents<Window>(_index_ecs_client, window);
        _ecs.addComponents<Background>(_index_ecs_client, Background("assets/space-background.jpg", 100, 100));
        _index_ecs_client++;
    }

    void Client::start()
    {

        if (!_udpClient->initialize("rtype_game/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeClientExceptions("Failed to initialize client");
        }

        _timer->init("rtype_game/config/client_config.conf", false);
        _udpClient->startReceiving();
        _ecs.init_basic_registry();
        init_ecs_client_registry();
        init_background();
        init_subscribe_event_bus();
        // Window window(800, 600, "My ECS Client Window");
        // Window window(1920, 1080, "R-Type");
        // sf::Texture texture;
        // sf::Sprite sprite;
        // if (!texture.loadFromFile("assets/background_2.png")) {
        //             throw std::runtime_error("Failed to load background texture from: ");
        //         }
        //         // std::cout << "Texture loaded successfully from: " << texturePath << std::endl;
        //         sprite.setTexture(texture);
                // sprite.setScale(800,600);
        _eventBus.emit(RTYPE_ACTIONS::START_LISTEN_EVENT, std::ref(_ecs._components_arrays), std::ref(_event_window_system));

        while (_running) {
            _timer->waitTPS();
            _eventBus.emit(RTYPE_ACTIONS::GET_WINDOW_EVENT, std::ref(_ecs._components_arrays), std::ref(_event_window_system), std::ref(_events));
            handle_event();
            _eventBus.emit(RTYPE_ACTIONS::UPDATE_POSITION, std::ref(_ecs._components_arrays), std::ref(_position_system), _timer);
            _ecs.displayPlayableEntityComponents();
            auto messages = _udpClient->fetchAllMessages();
            for (auto &[clientAddress, message] : messages) {
                try {
                    handle_message(message, clientAddress);
                } catch (std::exception &e) {
                    std::cerr << std::endl << e.what() << std::endl;
                }
            }
            _eventBus.emit(RTYPE_ACTIONS::RENDER, std::ref(_ecs._components_arrays), std::ref(_render_window_system));
            // window.getRenderWindow()->draw(sprite);
            //                 window.getRenderWindow()->display();
        }
        _eventBus.emit(RTYPE_ACTIONS::STOP_LISTEN_EVENT, std::ref(_ecs._components_arrays), std::ref(_event_window_system));
    }
}
