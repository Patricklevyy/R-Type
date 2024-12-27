/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#include "SFMLHandler.hpp"

namespace rtype
{
    SFMLHandler::SFMLHandler(Client &client)
        : _client(client)
    {
    }

    SFMLHandler::~SFMLHandler()
    {
    }

    void SFMLHandler::handleEvents(std::queue<sf::Event> &events)
    {
        while (!events.empty())
        {
            sf::Event event = events.front();
            events.pop();

            switch (event.type)
            {
            case sf::Event::Closed:
                _client._running = false;
                return;

            case sf::Event::KeyPressed:
                processKeyPressed(event);
                break;

            case sf::Event::KeyReleased:
                processKeyReleased(event);
                break;

            case sf::Event::MouseButtonPressed:
                processMouseButtonPressed(event);
                break;

            default:
                std::cout << "Unhandled event type." << std::endl;
                break;
            }
        }
    }

    void SFMLHandler::processKeyPressed(const sf::Event &event)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            // Close the client
            _client._running = false;
            return;
        }

        if (event.key.code == sf::Keyboard::D && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::RIGHT, ecs::direction::NO_CHANGE);
        }
        if (event.key.code == sf::Keyboard::Q && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::LEFT, ecs::direction::NO_CHANGE);
        }
        if (event.key.code == sf::Keyboard::Z && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::UP);
        }
        if (event.key.code == sf::Keyboard::S && !_client._in_menu)
        {
            _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::DOWN);
        }
        if (event.key.code == sf::Keyboard::A)
        {
            _client.send_server_create_room();
        }
        if (event.key.code == sf::Keyboard::B)
        {
            _client.send_server_join_room();
        }
        if (event.key.code == sf::Keyboard::Num1)
        {
            _client.set_window_filter(FILTER_MODE::Neutral);
        }
        if (event.key.code == sf::Keyboard::Num2)
        {
            _client.set_window_filter(FILTER_MODE::Inverted);
        }
        if (event.key.code == sf::Keyboard::Num3)
        {
            _client.set_window_filter(FILTER_MODE::Protanopia);
        }
        if (event.key.code == sf::Keyboard::Num4)
        {
            _client.set_window_filter(FILTER_MODE::Deuteranopia);
        }
        if (event.key.code == sf::Keyboard::Num5)
        {
            _client.set_window_filter(FILTER_MODE::Tritanopia);
        }
    }

    void SFMLHandler::processKeyReleased(const sf::Event &event)
    {
        if (!_client._in_menu)
        {
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Q)
            {
                _client.change_player_direction(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
            }
            if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S)
            {
                _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
            }
        }
    }

    void SFMLHandler::processMouseButtonPressed(const sf::Event &event)
    {
        (void)event;
        _client.handleMouseClick();
    }
}