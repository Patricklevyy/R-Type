/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Event_Bus
*/

#include "Client.hpp"

namespace rtype
{
    void Client::init_subscribe_event_bus()
    {
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
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITIONS, [this](const std::vector<std::any> &args) {
            (void)args;
            _position_system.updatePositions(_ecs._components_arrays, _timer->getTps(), _window_width, _window_height);
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_PARTIALS_POSITIONS_FROM_SERVER, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                std::list<std::pair<std::size_t, std::pair<float, float>>> entities = Command_checker::parse_update(message.params);

                while (!entities.empty()) {
                    auto it = ecs_server_to_client.find(std::get<0>(entities.front()));
                    if (it != ecs_server_to_client.end() && _player_system.getIndexPlayer(_ecs._components_arrays) != ecs_server_to_client[std::get<0>(entities.front())]) {
                        _update_entity_system.updateEntity(_ecs._components_arrays, entities.front(), ecs_server_to_client[std::get<0>(entities.front())]);
                    }
                    entities.pop_front();
                }
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: UPDATE POSSSS" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITIONS_FROM_SERVER, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                std::list<std::pair<std::size_t, std::pair<float, float>>> entities = Command_checker::parse_update(message.params);

                while (!entities.empty()) {
                    auto it = ecs_server_to_client.find(std::get<0>(entities.front()));
                    if (it != ecs_server_to_client.end() && _player_system.getIndexPlayer(_ecs._components_arrays) != ecs_server_to_client[std::get<0>(entities.front())]) {
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
        _eventBus.subscribe(RTYPE_ACTIONS::KILL_ENTITY, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                std::list<size_t> entities_id;
                std::stringstream ss(message.params);
                std::string token;

                while (std::getline(ss, token, ';')) {
                    entities_id.push_back(std::stoull(token));
                }
                killEntity(entities_id);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::CREATE_MONSTER, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                size_t x_pos = message.params.find("x=");
                size_t y_pos = message.params.find("y=");
                size_t type_pos = message.params.find("type=");

                if (x_pos == std::string::npos || y_pos == std::string::npos || type_pos == std::string::npos) {
                    throw std::runtime_error("Malformed params string");
                }

                float x = std::stof(message.params.substr(x_pos + 2, message.params.find(';', x_pos) - (x_pos + 2)));
                float y = std::stof(message.params.substr(y_pos + 2, message.params.find(';', y_pos) - (y_pos + 2)));
                int typeInt = std::stoi(message.params.substr(type_pos + 5));

                createEntity(message.id, x, y, static_cast<SPRITES>(typeInt));
            } catch (const std::exception &e) {
                std::cerr << "Error handling CREATE_MONSTER event: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::MOVE_BACKGROUND, [this](const std::vector<std::any> &args) {
            (void)args;
            _render_window_system.move_background(_ecs._components_arrays, _in_menu, _timer->getTps());
        });
        _eventBus.subscribe(RTYPE_ACTIONS::FAIL_LEVEL, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                add_level_status_screen(false, message);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::WIN_LEVEL, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                add_level_status_screen(true, message);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::REMOVE_ATH, [this](const std::vector<std::any> &args) {
            (void)args;

            _ath_system.removeLevels(_ecs);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PLAYER, [this](const std::vector<std::any> &args) {
            ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

            std::stringstream ss(message.params);
            std::string token;

            float x = 0.0f, y = 0.0f;

            std::getline(ss, token, ';');
            x = std::stof(token);

            std::getline(ss, token, ';');
            y = std::stof(token);

            createPlayer(message.id, x, y);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_SCORE, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                _score_system.updateScore(_ecs._components_arrays, message.params);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UP_VELOCITY, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                _bonus_system.changePlayerVelocity(_ecs._components_arrays, _player_system.getIndexPlayer(_ecs._components_arrays), _gameplay_factory->getVelocityBoostBonus());

            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::DOWN_VELOCITY, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                _bonus_system.changePlayerVelocity(_ecs._components_arrays, _player_system.getIndexPlayer(_ecs._components_arrays), -_gameplay_factory->getVelocityBoostBonus());

            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::PUT_SHIELD, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                _player_system.changePlayerSprite(_ecs._components_arrays, ecs_server_to_client[std::stoi(message.params)], SPRITES::SHIP_SHIELD);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::REMOVE_SHIELD, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                _player_system.changePlayerSprite(_ecs._components_arrays, ecs_server_to_client[std::stoi(message.params)], SPRITES::MY_PLAYER_SHIP);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
    }
}
