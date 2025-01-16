/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#ifndef SFMLHANDLER_HPP_
#define SFMLHANDLER_HPP_

    #include "Client.hpp"
    namespace rtype
    {
        class Client;

        class SFMLHandler {
            public:
                SFMLHandler(Client &client);
                ~SFMLHandler();

                void handleEvents(std::queue<sf::Event> &);
                void bindKey(sf::Keyboard::Key, sf::Keyboard::Key);
                void unbind(sf::Keyboard::Key);
                void resetBind();

            private:
                void processKeyPressed(const sf::Event &event);
                void processKeyReleased(const sf::Event &event);
                void processMouseButtonPressed(const sf::Event &event);
                void processMouseButtonReleased(const sf::Event &event);
                void init_keys();

                std::map<sf::Keyboard::Key, sf::Keyboard::Key> _keyBindings;

                Client &_client;
                
            };
    }

#endif /* !SFMLHANDLER_HPP_ */
