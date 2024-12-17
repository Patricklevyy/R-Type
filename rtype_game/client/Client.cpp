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
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_CLIENT, [this](const std::vector<std::any> &args) {
            ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

            init_game(message);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, [this](const std::vector<std::any> &args) {
            try {
                std::tuple<ecs::direction, ecs::direction, size_t> _x_y_index = std::any_cast<std::reference_wrapper<std::tuple<ecs::direction, ecs::direction, size_t>>>(args[0]).get();
                _direction_system.updatePlayerDirection(_ecs._components_arrays, std::get<0>(_x_y_index), std::get<1>(_x_y_index), std::get<2>(_x_y_index));
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_PLAYER_POSITION, [this](const std::vector<std::any> &args) {
            (void)args;
            _position_system.updatePlayerPositions(_ecs._components_arrays, _timer->getTps(), _ecs.getIndexPlayer());
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                std::list<std::tuple<std::size_t, std::pair<float, float>, int>> entities = Command_checker::parse_update(message.params);

                while (!entities.empty()) {
                    auto it = ecs_server_to_client.find(std::get<0>(entities.front()));
                    if (it != ecs_server_to_client.end() && _ecs.getIndexPlayer() != ecs_server_to_client[std::get<0>(entities.front())]) {
                        _update_entity_system.updateEntity(_ecs._components_arrays, entities.front(), ecs_server_to_client[std::get<0>(entities.front())]);
                    }
                    entities.pop_front();
                }
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: UPDATE POSSSS" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::CREATE_TEAMMATE, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                size_t separator_pos = message.params.find(';');

                std::string x_part = message.params.substr(0, separator_pos);
                std::string y_part = message.params.substr(separator_pos + 1);

                float x = std::stof(x_part.substr(2));
                float y = std::stof(y_part.substr(2));

                createEntity(message.id, x, y, SPRITES::OTHER_PLAYER_SHIP);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::RENDER_WINDOW, [this](const std::vector<std::any> &args) {
            (void)args;
            _render_window_system.render(_ecs._components_arrays);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PROJECTILE, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                createProjectile(message);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::KILL_PROJECTILES, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                std::list<size_t> entities_id;
                std::stringstream ss(message.params);
                std::string token;

                while (std::getline(ss, token, ';')) {
                    entities_id.push_back(std::stoull(token));
                }
                killProjectiles(entities_id);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::CREATE_MONSTER, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                size_t separator_pos = message.params.find(';');
                float x = std::stof(message.params.substr(0, separator_pos).substr(2));
                float y = std::stof(message.params.substr(separator_pos + 1).substr(2));

                createEntity(message.id, x, y, SPRITES::MONSTER);
            } catch (const std::exception &e) {
                std::cerr << "Error handling CREATE_MONSTER event: " << e.what() << std::endl;
            }
        });
    }

    void Client::init_game(ecs::udp::Message &message)
    {
        size_t pos = message.params.find(':');

        std::string player_room = message.params.substr(0, pos);
        std::string entities = message.params.substr(pos + 1);

        std::cout << "PLAYER : " << player_room << "ENTITIES : " << entities << std::endl;
        std::tuple<float, float, int> pos_port = Command_checker::parsePositionAndRoomPort(player_room);

        setRoomAdress(message.id, std::get<2>(pos_port));
        createPlayer(message.id, std::get<0>(pos_port), std::get<1>(pos_port));
        updateEntitiesFirstConnexion(entities);
        _in_menu = false;
    }

    void Client::killProjectiles(std::list<size_t> entities_id)
    {
        size_t index_ecs_server;
        size_t index_ecs_client;

        for (const auto &id : entities_id) {
            auto it = ecs_server_to_client.find(id);
            if (it != ecs_server_to_client.end()) {
                index_ecs_client = it->second;
                ecs_server_to_client.erase(it);

                it = ecs_client_to_server.find(index_ecs_client);
                ecs_client_to_server.erase(it);

                _ecs.killEntityFromRegistry<ecs::Position>(index_ecs_client);
                _ecs.killEntityFromRegistry<Health>(index_ecs_client);
                _ecs.killEntityFromRegistry<Displayable>(index_ecs_client);
                _ecs.addDeadEntity(index_ecs_client);
            }
        }
    }

    void Client::updateEntitiesFirstConnexion(const std::string &message)
    {
        std::vector<std::tuple<std::pair<float, float>, int, int>> entities = Command_checker::parseUpdateEntities(message);

        while (!entities.empty()) {
            std::tuple<std::pair<float, float>, int, int> entity = entities.back();
            std::cout << "XX : " << std::get<0>(entity).first << "yy : " << std::get<0>(entity).second << std::endl;
            createEntity(std::get<1>(entity), std::get<0>(entity).first, std::get<0>(entity).second, static_cast<SPRITES>(std::get<2>(entity)));
            entities.pop_back();
        }
    }

    void Client::createEntity(unsigned int server_id, float x, float y, SPRITES sprite_id)
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = _index_ecs_client;
            _index_ecs_client++;
        }
        std::cout << "JE CREATE : " << index << std::endl;
        ecs::Position position(x, y);
        Displayable displayable(sprite_id, x, y);
        Health health;

        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Displayable>(index, displayable);

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::createProjectile(ecs::udp::Message &message)
    {
        float x = 0.0f, y = 0.0f;
        int type = 0;

        std::vector<std::string> parts;
        std::stringstream ss(message.params);
        std::string part;

        while (std::getline(ss, part, ';')) {
            parts.push_back(part);
        }

        x = std::stof(parts[0].substr(parts[0].find('=') + 1));
        y = std::stof(parts[1].substr(parts[1].find('=') + 1));
        type = std::stoi(parts[2].substr(parts[2].find('=') + 1));

        SPRITES spriteType = static_cast<SPRITES>(type);

        createEntity(message.id, x, y, spriteType);
    }

    void Client::send_server_new_shoot()
    {
        ecs::udp::Message message;
        std::vector<char> buffer;
        std::pair<float, float> player_positions = _position_system.getPlayerPosition(_ecs.getIndexPlayer(), _ecs._components_arrays);

        message.id = 0;
        message.action = RTYPE_ACTIONS::PLAYER_SHOOT;
        message.params = "x=" + std::to_string(player_positions.first + 130) + ";y=" + std::to_string(player_positions.second + 20) + ";dir_x=" + std::to_string(ecs::direction::RIGHT) + ";dir_y=" + std::to_string(ecs::direction::NO_DIRECTION);

        _message_compressor.serialize(message, buffer);

        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::createMonster(ecs::udp::Message &message)
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();

        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = _index_ecs_client;
            _index_ecs_client++;
        }
        std::unordered_map<std::string, std::string> res = MessageChecker::parseResponse(message.params);
        if (res.find("x") == res.end() || res.find("y") == res.end()) {
            std::cerr << "Error: Missing x or y in message parameters" << std::endl;
            return;
        }
        int x = std::stof(res["x"]);
        int y = std::stof(res["y"]);
        ecs::Position position(x, y);
        Displayable displayable(SPRITES::MONSTER, x, y);
        Health health;

        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Displayable>(index, displayable);

        std::cout << "Monstre créé à l'index : " << index << " (" << x << ", " << y << ")" << std::endl;
    }

    void Client::setRoomAdress(unsigned int server_id, int port)
    {
        std::string ip_port = Command_checker::check_adress(port, _udpClient->getServerIp());
        _udpClient->setDefaultAddress(ip_port);
    }

    void Client::createPlayer(unsigned int server_id, float x, float y)
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = _index_ecs_client;
            _index_ecs_client++;
        }

        ecs::Direction direction;
        ecs::Playable playable(_name);
        ecs::Position position(x, y);
        ecs::Velocity velocity;
        Displayable displayable(SPRITES::MY_PLAYER_SHIP, x, y);
        Health health;

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Playable>(index, playable);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Displayable>(index, displayable);
        _ecs.addComponents<Health>(index, health);

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::handle_message(std::vector<char> &message, std::string clientAddr)
    {
        ecs::udp::Message mes;
        _message_compressor.deserialize(message, mes);
        _mes_checker.checkAction(mes);
        std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << std::endl;
        rtype::RTYPE_ACTIONS action = static_cast<rtype::RTYPE_ACTIONS>(mes.action);
        _eventBus.emit(action, std::ref(mes));
    }

    void Client::send_server_player_direction(ecs::direction x, ecs::direction y)
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = ecs_client_to_server[_ecs.getIndexPlayer()];
        ;
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
        while (!_events.empty()) {
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
                    mess.params = "room_name=room1;client_name=jean;x=" + std::to_string(_window_width) + ";y=" + std::to_string(_window_height);

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
                    mess.params = "room_name=room1;client_name=patrick;x=" + std::to_string(_window_width) + ";y=" + std::to_string(_window_height);

                    _message_compressor.serialize(mess, buffer);

                    std::cout << "je send" << std::endl;
                    if (_udpClient->sendMessageToDefault(buffer)) {
                        std::cout << "Message sent: " << std::endl;
                    } else {
                        std::cout << "failed " << std::endl;
                    }
                }
                if (event.key.code == sf::Keyboard::M) {
                    ecs::udp::Message mess;
                    std::vector<char> buffer;
                    mess.id = 0;
                    mess.action = RTYPE_ACTIONS::CREATE_MONSTER;
                    mess.params = "x=800;y=800";

                    _message_compressor.serialize(mess, buffer);

                    if (_udpClient->sendMessageToDefault(buffer)) {
                        std::cout << "Request sent to create a monster" << std::endl;
                    } else {
                        std::cerr << "Failed to send request" << std::endl;
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
            case sf::Event::MouseButtonPressed:
                if (event.mouseButton.button == sf::Mouse::Left) {
                    send_server_new_shoot();
                }

            default:
                std::cout << "Événement non traité." << std::endl;
                break;
            }
        }
    }

    void Client::init_window_and_background()
    {
        Window window(_window_width, _window_height, "R-Type");
        _ecs.addComponents<Window>(_index_ecs_client, window);
        _ecs.addComponents<Displayable>(_index_ecs_client, Displayable(SPRITES::BACKGROUND, 0, 0));
        _ecs.addComponents<ecs::Position>(_index_ecs_client, ecs::Position(0, 0));
        _index_ecs_client++;
    }

    void Client::init_window_size(const std::string &file_path)
    {
        libconfig::Config cfg; // Objet Config pour lire le fichier

        try {
            cfg.readFile(file_path.c_str());

            const libconfig::Setting &root = cfg.getRoot();
            const libconfig::Setting &client = root["client"];

            if (!client.lookupValue("window_width", _window_width)) {
                std::cerr << "Erreur : 'window_x' introuvable dans le fichier de configuration." << std::endl;
            }

            if (!client.lookupValue("window_height", _window_height)) {
                std::cerr << "Erreur : 'window_y' introuvable dans le fichier de configuration." << std::endl;
            }
        } catch (const libconfig::FileIOException &fioex) {
            std::cerr << "Erreur : Impossible de lire le fichier de configuration." << std::endl;
        } catch (const libconfig::ParseException &pex) {
            std::cerr << "Erreur de parsing au niveau " << pex.getFile()
                      << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Erreur : Paramètre introuvable dans le fichier de configuration." << std::endl;
        }
    }

    void Client::init_all()
    {
        if (!_udpClient->initialize("rtype_game/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeClientExceptions("Failed to initialize client");
        }
        init_window_size("rtype_game/config/client_config.conf");
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
                    std::cerr << std::endl
                              << e.what() << std::endl;
                }
            }
            // _ecs.displayPlayableEntityComponents();
            _eventBus.emit(RTYPE_ACTIONS::RENDER_WINDOW);
        }
        _eventBus.emit(RTYPE_ACTIONS::STOP_LISTEN_EVENT);
    }
}
