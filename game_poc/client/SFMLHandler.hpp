/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#ifndef SFMLHANDLER_HPP_
#define SFMLHANDLER_HPP_

    #include "Client.hpp"

    namespace poc_game
    {
        class Client;

        class SFMLHandler {
            public:
                SFMLHandler(Client &client);
                ~SFMLHandler();

                void handleEvents(std::queue<sf::Event> &);

            private:
                void processMouseButtonPressed(const sf::Event &);

                Client &_client;
            };
    }

#endif /* !SFMLHANDLER_HPP_ */
