/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#ifndef SFMLHANDLER_HPP_
#define SFMLHANDLER_HPP_

    #include "Client.hpp"
    #include "menu/Menu.hpp"

    namespace rtype
    {
        class Client;

        class SFMLHandler {
            public:
                SFMLHandler(Client &client);
                ~SFMLHandler();

                void handleEvents(std::queue<sf::Event> &);
                void renderMenu(sf::RenderWindow &window);


            private:
                void processKeyPressed(const sf::Event &event);
                void processKeyReleased(const sf::Event &event);
                void processMouseButtonPressed(const sf::Event &event);
                void processMouseButtonReleased(const sf::Event &event);

                Client &_client;
                std::shared_ptr<Menu> _menu;
                sf::Font _font;
            };
    }

#endif /* !SFMLHANDLER_HPP_ */
