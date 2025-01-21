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

        /**
         * @class SFMLHandler
         * @brief Class that handles user input events for the client using SFML.
         */
        class SFMLHandler {
            public:
                /**
                  * @brief Constructor for the SFMLHandler class.
                  * @param client A reference to the Client object that manages game logic.
                  */
                SFMLHandler(Client &client);

                /**
                 * @brief Destructor for the SFMLHandler class.
                 */
                ~SFMLHandler();

                /**
                 * @brief Handles a queue of SFML events.
                 * @param events A reference to a queue of events to process.
                 */
                void handleEvents(std::queue<sf::Event> &);

                /**
                 * @brief Resets the key bindings to their default values.
                 */
                void resetBind();

                /**
                 * @brief Returns the current key bindings.
                 * @return A map associating keys with actions.
                 */
                std::map<sf::Keyboard::Key, sf::Keyboard::Key> getKeyBindings();

                /**
                 * @brief Updates the key bindings with a new configuration.
                 * @param newBindings A map representing the new key associations.
                 */
                void updateKeyBindings(const std::map<sf::Keyboard::Key, sf::Keyboard::Key> &newBindings);

            private:
                /**
                 * @brief Processes the event of a key press.
                 * @param event The event containing the key press information.
                 */
                void processKeyPressed(const sf::Event &event);

                /**
                 * @brief Processes the event of a key release.
                 * @param event The event containing the key release information.
                 */
                void processKeyReleased(const sf::Event &event);

                /**
                 * @brief Processes the event of a mouse button press.
                 * @param event The event containing the mouse button press information.
                 */
                void processMouseButtonPressed(const sf::Event &event);

                /**
                 * @brief Processes the event of a mouse button release.
                 * @param event The event containing the mouse button release information.
                 */
                void processMouseButtonReleased(const sf::Event &event);

                /**
                 * @brief Initializes the default key bindings for game actions.
                 */
                void init_keys();

                std::map<sf::Keyboard::Key, sf::Keyboard::Key> _keyBindings;

                Client &_client;

            };
    }

#endif /* !SFMLHANDLER_HPP_ */
