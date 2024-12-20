/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Event_Sfml
*/

#include "Client.hpp"

namespace rtype
{
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
                    mess.secret_key = _udpClient->getSecretKey();
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
                    mess.secret_key = _udpClient->getSecretKey();
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
                    mess.secret_key = _udpClient->getSecretKey();
                    mess.params = "x=800;y=800";

                    _message_compressor.serialize(mess, buffer);

                    if (_udpClient->sendMessageToDefault(buffer)) {
                        std::cout << "Request sent to create a monster" << std::endl;
                    } else {
                        std::cerr << "Failed to send request" << std::endl;
                    }
                }
                if (event.key.code == sf::Keyboard::Num1) {
                    _set_filter_system.setFilter(_ecs._components_arrays, FILTER_MODE::Neutral);
                }
                if (event.key.code == sf::Keyboard::Num2) {
                    _set_filter_system.setFilter(_ecs._components_arrays, FILTER_MODE::Inverted);
                }
                if (event.key.code == sf::Keyboard::Num3) {
                    _set_filter_system.setFilter(_ecs._components_arrays, FILTER_MODE::Protanopia);
                }
                if (event.key.code == 51) {
                    _set_filter_system.setFilter(_ecs._components_arrays, FILTER_MODE::Deuteranopia);
                }
                if (event.key.code == sf::Keyboard::Num5) {
                    _set_filter_system.setFilter(_ecs._components_arrays, FILTER_MODE::Tritanopia);
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
                {
                    std::pair<bool, LEVELS> isLevelChosen = _ath_system.isLevelClicked(_ecs._components_arrays);
                    // Si un niveau est sélectionné, effectuer une action
                    if (isLevelChosen.first) {
                        send_server_start_game(isLevelChosen.second);
                        _ath_system.removeLevels(_ecs);
                    } else if (_ath_system.isLooseOrWinClicked(_ecs._components_arrays)) {
                        restart_game();
                    } else if (_ecs.getIndexPlayer() != -1) {
                        send_server_new_shoot();
                    }
                }
                break;
            default:
                std::cout << "Événement non traité." << std::endl;
                break;
            }
        }
    }
}
