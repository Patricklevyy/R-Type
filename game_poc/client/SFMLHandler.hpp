/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#ifndef SFMLHANDLER_HPP_
#define SFMLHANDLER_HPP_

    #include "Client.hpp"
    #include <SFML/Graphics.hpp>

    namespace poc_game
    {
        class Client;

        /**
         * @class SFMLHandler
         * @brief Handles events from SFML, such as mouse and keyboard interactions.
         */
        class SFMLHandler {
            public:
                /**
                 * @brief Constructs the SFMLHandler object.
                 * @param client The Client object which this handler will interact with.
                 */
                SFMLHandler(Client &client);

                /**
                 * @brief Destructor for SFMLHandler class.
                 */
                ~SFMLHandler();

                /**
                 * @brief Handles SFML events by processing each event in the queue.
                 * @param events The queue of events to be processed.
                 */
                void handleEvents(std::queue<sf::Event> &);

            private:
                /**
                 * @brief Processes mouse button press events.
                 * @param event The event triggered when a mouse button is pressed.
                 */
                void processMouseButtonPressed(const sf::Event &);

                Client &_client;
            };
    }

#endif /* !SFMLHANDLER_HPP_ */
