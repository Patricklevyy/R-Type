/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

/**
 * @file SFMLHandler.hpp
 * @brief Header file for the SFMLHandler class.
 *
 * This file contains the declaration of the SFMLHandler class, which is responsible
 * for managing and handling user input events (such as keyboard and mouse events)
 * via the SFML library. It also handles key binding and event processing logic.
 */

#ifndef SFMLHANDLER_HPP_
#define SFMLHANDLER_HPP_

#include "Client.hpp"

namespace rtype
{
    class Client;

    /**
     * @class SFMLHandler
     * @brief A class that handles user input events using SFML.
     *
     * The SFMLHandler class is responsible for handling events from the keyboard
     * and mouse using the Simple and Fast Multimedia Library (SFML). It supports
     * key bindings, event processing, and integration with the `Client` class.
     */
    class SFMLHandler {
      public:
        /**
         * @brief Constructor for the SFMLHandler class.
         *
         * Initializes the SFMLHandler and binds it to the specified client.
         *
         * @param client The Client object to associate with this handler.
         */
        SFMLHandler(Client &client);

        /**
         * @brief Destructor for the SFMLHandler class.
         */
        ~SFMLHandler();

        /**
         * @brief Handles events from a queue.
         *
         * Processes events related to keyboard and mouse interactions and triggers
         * the appropriate actions. It handles events passed through the `sf::Event`
         * object queue.
         *
         * @param events A queue of SFML events to be processed.
         */
        void handleEvents(std::queue<sf::Event> &events);

        /**
         * @brief Binds a new key to a specific action.
         *
         * Allows a key press to be remapped to a different action. It binds a key
         * from the keyboard input to another key or action.
         *
         * @param key A key to bind from the keyboard.
         * @param bindTo A key to bind to (remaps the action of `key`).
         */
        void bindKey(sf::Keyboard::Key key, sf::Keyboard::Key bindTo);

        /**
         * @brief Unbinds a key.
         *
         * Removes the current binding of the specified key, making it unresponsive
         * to the previous action.
         *
         * @param key The key to unbind.
         */
        void unbind(sf::Keyboard::Key key);

        /**
         * @brief Resets all key bindings to default values.
         *
         * Resets all the keys that were bound using `bindKey` to their default
         * actions or states.
         */
        void resetBind();

      private:
        /**
         * @brief Processes when a key is pressed.
         *
         * Handles the event when a key is pressed. It triggers actions based on
         * the current key bindings.
         *
         * @param event The key press event.
         */
        void processKeyPressed(const sf::Event &event);

        /**
         * @brief Processes when a key is released.
         *
         * Handles the event when a key is released. It updates the state of the key.
         *
         * @param event The key release event.
         */
        void processKeyReleased(const sf::Event &event);

        /**
         * @brief Processes when a mouse button is pressed.
         *
         * Handles the event when a mouse button is pressed, triggering the action
         * associated with that mouse interaction.
         *
         * @param event The mouse button press event.
         */
        void processMouseButtonPressed(const sf::Event &event);

        /**
         * @brief Processes when a mouse button is released.
         *
         * Handles the event when a mouse button is released.
         *
         * @param event The mouse button release event.
         */
        void processMouseButtonReleased(const sf::Event &event);

        /**
         * @brief Initializes default key bindings.
         *
         * Sets up the default key bindings for various actions in the game.
         */
        void init_keys();

        /**
         * @brief A map for storing key bindings.
         *
         * This map associates a key with another key to simulate key remapping.
         */
        std::map<sf::Keyboard::Key, sf::Keyboard::Key> _keyBindings;

        /**
         * @brief Reference to the client object.
         *
         * The client object is needed to execute specific actions based on input events.
         */
        Client &_client;
    };
}

#endif /* !SFMLHANDLER_HPP_ */
