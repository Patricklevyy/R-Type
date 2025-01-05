/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#include "SFMLHandler.hpp"

namespace poc_game
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
            case sf::Event::MouseButtonPressed:
                processMouseButtonPressed(event);
                break;

            default:
                break;
            }
        }
    }

    void SFMLHandler::processMouseButtonPressed(const sf::Event &event)
    {
        (void)event;
        _client.handleMouseClick();
    }
}