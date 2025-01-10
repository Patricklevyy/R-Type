/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#include "SFMLHandler.hpp"

namespace rtype
{
    SFMLHandler::SFMLHandler(Client &client) : _client(client), _menu(nullptr)
    {
        if (!_font.loadFromFile("assets/fonts/Georgia Regular font.ttf")) {
            throw std::runtime_error("Failed to load font");
        }
        _menu = std::make_shared<Menu>(_font);
        _menu->addRoom("Room 1", 2);
        _menu->addRoom("Room 2", 4);
        _menu->addRoom("Room 3", 1);
    }

    SFMLHandler::~SFMLHandler()
    {
    }

    void SFMLHandler::handleEvents(std::queue<sf::Event> &events)
    {
        while (!events.empty()) {
            sf::Event event = events.front();
            events.pop();

            if (_client._in_menu) {
                _menu->handleEvent(event);

                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mousePos(
                        event.mouseButton.x, event.mouseButton.y);
                    _menu->handleClick(mousePos, "Patoche");

                    if (!_menu->getSelectedRoom().empty()) {
                        _client.send_server_join_room(
                            _menu->getSelectedRoom(), "Patoche");
                        _client._in_menu = false;
                    }
                }

                if (event.type == sf::Event::KeyPressed
                    && event.key.code == sf::Keyboard::Enter) {
                    if (_menu->isCreatingRoom()) {
                        std::string roomName = _menu->getRoomName();
                        if (!roomName.empty()) {
                            _client.send_server_create_room(roomName);
                            _menu->addRoom(roomName, 0);
                            _menu->clearRoomInput();
                            _menu->stopCreatingRoom();
                        }
                    }
                }
                continue;
            }

            switch (event.type) {
                case sf::Event::Closed: _client._running = false; return;

                case sf::Event::KeyPressed: processKeyPressed(event); break;

                case sf::Event::KeyReleased: processKeyReleased(event); break;

                case sf::Event::MouseButtonPressed:
                    processMouseButtonPressed(event);
                    break;

            case sf::Event::MouseButtonReleased:
                processMouseButtonReleased(event);
                break;

            default:
                std::cout << "Unhandled event type." << std::endl;
                break;
            }
        }
    }

    void SFMLHandler::renderMenu(sf::RenderWindow &window)
    {
        window.clear(sf::Color::White);
        _menu->draw(window);
        window.display();
    }

    void SFMLHandler::processKeyPressed(const sf::Event &event)
    {
        if (event.key.code == sf::Keyboard::Escape) {
            // Close the client
            _client._running = false;
            return;
        }

        if (event.key.code == sf::Keyboard::D && !_client._in_menu) {
            _client.change_player_direction(
                ecs::direction::RIGHT, ecs::direction::NO_CHANGE);
        }
        if (event.key.code == sf::Keyboard::Q && !_client._in_menu) {
            _client.change_player_direction(
                ecs::direction::LEFT, ecs::direction::NO_CHANGE);
        }
        if (event.key.code == sf::Keyboard::Z && !_client._in_menu) {
            _client.change_player_direction(
                ecs::direction::NO_CHANGE, ecs::direction::UP);
        }
        if (event.key.code == sf::Keyboard::S && !_client._in_menu) {
            _client.change_player_direction(
                ecs::direction::NO_CHANGE, ecs::direction::DOWN);
        }
        // if (event.key.code == sf::Keyboard::A)
        // {
        //     _client.send_server_create_room("uneroom");
        // }
        // if (event.key.code == sf::Keyboard::B)
        // {
        //     _client.send_server_join_room("uneroom", "Patoche");
        // }
        if (event.key.code == sf::Keyboard::Num1) {
            _client.set_window_filter(FILTER_MODE::Neutral);
        }
        if (event.key.code == sf::Keyboard::Num2) {
            _client.set_window_filter(FILTER_MODE::Inverted);
        }
        if (event.key.code == sf::Keyboard::Num3) {
            _client.set_window_filter(FILTER_MODE::Protanopia);
        }
        if (event.key.code == sf::Keyboard::Num4) {
            _client.set_window_filter(FILTER_MODE::Deuteranopia);
        }
        if (event.key.code == sf::Keyboard::Num5) {
            _client.set_window_filter(FILTER_MODE::Tritanopia);
        }
    }

    void SFMLHandler::processKeyReleased(const sf::Event &event)
    {
        if (!_client._in_menu) {
            if (event.key.code == sf::Keyboard::D
                || event.key.code == sf::Keyboard::Q) {
                _client.change_player_direction(
                    ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
            }
            if (event.key.code == sf::Keyboard::Z
                || event.key.code == sf::Keyboard::S) {
                _client.change_player_direction(
                    ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
            }
        }
    }

    void SFMLHandler::processMouseButtonPressed(const sf::Event &event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _client.handleMousePress(); // Commence un tir
        }
    }

    void SFMLHandler::processMouseButtonReleased(const sf::Event &event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _client.handleMouseRelease(); // Termine le tir
        }
    }
} // namespace rtype