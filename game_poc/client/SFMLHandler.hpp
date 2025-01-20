/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#ifndef SFMLHANDLER_HPP_
#define SFMLHANDLER_HPP_

    #include "Client.hpp"

    /**
     * @file SFMLHandler.hpp
     * @brief Header file for the SFMLHandler class.
     */

    namespace poc_game
    {
        /**
         * @class SFMLHandler
         * @brief Handles SFML events for the client.
         */
        class SFMLHandler {
            public:
                /**
                 * @brief Constructor for SFMLHandler.
                 * @param client Reference to the Client object.
                 */
                SFMLHandler(Client &client);

                /**
                 * @brief Destructor for SFMLHandler.
                 */
                ~SFMLHandler();

                /**
                 * @brief Handles SFML events.
                 * @param events Queue of SFML events to handle.
                 */
                void handleEvents(std::queue<sf::Event> &events);

            private:
                /**
                 * @brief Processes mouse button pressed events.
                 * @param event The SFML event to process.
                 */
                void processMouseButtonPressed(const sf::Event &event);

                Client &_client; ///< Reference to the Client object.
        };
    }

#endif /* !SFMLHANDLER_HPP_ */
