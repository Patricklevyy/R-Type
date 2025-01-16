/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#include "SFMLHandler.hpp"

namespace rtype
{
    SFMLHandler::SFMLHandler(Client &client) : _client(client)
    {
        init_keys();
    }

    SFMLHandler::~SFMLHandler()
    {
    }

    void SFMLHandler::init_keys()
    {
        _keyBindings = {
            {sf::Keyboard::A, sf::Keyboard::A},
            {sf::Keyboard::B, sf::Keyboard::B},
            {sf::Keyboard::Z, sf::Keyboard::Z},
            {sf::Keyboard::S, sf::Keyboard::S},
            {sf::Keyboard::Q, sf::Keyboard::Q},
            {sf::Keyboard::D, sf::Keyboard::D}
        };
    }

    void SFMLHandler::bindKey(sf::Keyboard::Key former_key, sf::Keyboard::Key new_key)
    {
        _keyBindings[former_key] = new_key;
    }

    void SFMLHandler::unbind(sf::Keyboard::Key key)
    {
        _keyBindings[key] = key;
    }


    void SFMLHandler::resetBind()
    {
        init_keys();
    }


    void SFMLHandler::handleEvents(std::queue<sf::Event> &events)
    {
        while (!events.empty()) {
            sf::Event event = events.front();
            events.pop();

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
                break;
            }
        }
    }

    void SFMLHandler::processKeyPressed(const sf::Event &event)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            _client._running = false;
            return;
        }

        if (event.key.code == _keyBindings[sf::Keyboard::D] && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::RIGHT, ecs::direction::NO_CHANGE);
        }
        if (event.key.code == _keyBindings[sf::Keyboard::Q] && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::LEFT, ecs::direction::NO_CHANGE);
        }
        if (event.key.code == _keyBindings[sf::Keyboard::Z] && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::UP);
        }
        if (event.key.code == _keyBindings[sf::Keyboard::S] && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::DOWN);
        }
        if (event.key.code == _keyBindings[sf::Keyboard::A])
        {
            _client.send_server_create_room();
        }
        if (event.key.code == _keyBindings[sf::Keyboard::B])
        {
            _client.send_server_join_room();
        }
        if (event.key.code == sf::Keyboard::Num1)
        {
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
        if (!_client._in_menu)
        {
            if (event.key.code == _keyBindings[sf::Keyboard::D] || event.key.code == _keyBindings[sf::Keyboard::Q])
            {
                _client.change_player_direction(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
            }
            if (event.key.code == _keyBindings[sf::Keyboard::Z] || event.key.code == _keyBindings[sf::Keyboard::S])
            {
                _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
            }
        }
    }

    void SFMLHandler::processMouseButtonPressed(const sf::Event &event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _client.handleMousePress();
        }
    }

    void SFMLHandler::processMouseButtonReleased(const sf::Event &event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _client.handleMouseRelease();
        }
    }
} // namespace rtype