/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Event_Bus
*/

#include "Client.hpp"

namespace poc_game
{
    void Client::init_subscribe_event_bus()
    {
        _eventBus.subscribe(POC_GAME_ACTIONS::START_LISTEN_EVENT, [this](const std::vector<std::any> &args) {
            (void)args;
            _event_window_system.startListening(_ecs._components_arrays);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::STOP_LISTEN_EVENT, [this](const std::vector<std::any> &args) {
            (void)args;
            _event_window_system.stopListening();
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::RENDER_WINDOW, [this](const std::vector<std::any> &args) {
            (void)args;
            _render_window_system.render(_ecs._components_arrays);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::CREATE_CLIENT, [this](const std::vector<std::any> &args) {
            ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

            init_game(message);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::CREATE_PLAYER, [this](const std::vector<std::any> &args) {
            ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

            restart_game(message);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::START, [this](const std::vector<std::any> &args) {
            ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

            init_game(message);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::JUMP, [this](const std::vector<std::any> &args) {
            ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

            init_game(message);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::UPDATE_POSITIONS_FROM_SERVER, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                std::list<std::tuple<std::size_t, float, float>> entities = Utils::parse_update(message.params);

                while (!entities.empty()) {
                    _update_entity_system.updateEntity(_ecs._components_arrays, ecs_server_to_client[std::get<0>(entities.front())], std::get<1>(entities.front()), std::get<2>(entities.front()));
                    entities.pop_front();
                }
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: UPDATE POSSSS" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::KILL_ENTITY, [this](const std::vector<std::any> &args) {
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
        _eventBus.subscribe(POC_GAME_ACTIONS::FAIL_LEVEL, [this](const std::vector<std::any> &args) {
            try {
                auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();
                 (void)message;
                add_level_status_screen();
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::SPAWN_PIPE, [this](const std::vector<std::any> &args) {
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

                SPRITES spriteType = static_cast<SPRITES>(typeInt);

                createEntity(message.id, x, y, spriteType);
            } catch (const std::exception &e) {
                std::cerr << "Error handling CREATE_MONSTER event: " << e.what() << std::endl;
            }
        });
        // _eventBus.subscribe(RTYPE_ACTIONS::WIN_LEVEL, [this](const std::vector<std::any> &args) {
        //     try {
        //         auto &message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

        //         add_level_status_screen(true, message);
        //     } catch (const std::bad_any_cast &e) {
        //         std::cerr << "Error during event handling: " << e.what() << std::endl;
        //     }
        // });
        // _eventBus.subscribe(RTYPE_ACTIONS::REMOVE_ATH, [this](const std::vector<std::any> &args) {
        //     (void)args;

        //     _ath_system.removeLevels(_ecs);
        // });
        // _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PLAYER, [this](const std::vector<std::any> &args) {
        //     ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

        //     std::stringstream ss(message.params);
        //     std::string token;

        //     float x = 0.0f, y = 0.0f;

        //     std::getline(ss, token, ';');
        //     x = std::stof(token);

        //     std::getline(ss, token, ';');
        //     y = std::stof(token);

        //     createPlayer(message.id, x, y);
        // });
    }
}
