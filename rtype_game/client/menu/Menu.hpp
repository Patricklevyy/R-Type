/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <SFML/Graphics.hpp>
#include <memory>
#include "../SFMLHandler.hpp"
#include "InputScreen.hpp"
#include "RoomHandling.hpp"
#include "TextInput.hpp"
#include "Settings.hpp"

namespace rtype
{
    class Client;
    /**
     * @class Menu
     * @brief A class to manage the Menu of the game.
     */
    class Menu {
      public:
        /**
         * @brief A class to manage the Menu of the game.
         * @param window the window that will display the menu.
         * @param name name of the window.
         * @param client The client that display the menu.
         */
        Menu(sf::RenderWindow &window, const std::string &name, Client &client);

        /**
         * @brief Destructor for the class Menu.
         */
        ~Menu() {};

        /**
         * @brief function that will run the game.
         * @param bool say if the menu is actually used or not.
         */
        void run(bool &);

        /**
         * @brief Function to handle actions in the lenu.
         * @param in_menu bool that says if the player is in menu or not.
         */
        void handleEvents(bool &_in_menu);

        /**
         * @brief Function to update the menu.
         */
        void update();

        /**
         * @brief Function to render the menu.
         */
        void render();

        /**
         * @brief Function to get the player name.
         */
        std::string getPlayerName() const { return _playerName; }

        /**
         * @brief Get the created room.
         */
        std::string getCreatedRoom() const { return _createdRoom; }

        std::shared_ptr<RoomHandling> _roomHandling;
        std::shared_ptr<TextInput> _textInput;

        /**
         * @brief Synchronisation of the rooms.
         */
        void syncRooms();
        std::vector<std::pair<std::string, int>> roomsList;

        /**
         * @brief Event to join a room, and play game.
         */
        void joinRoomEvent();

      protected:
      private:
        sf::RenderWindow &_window;
        sf::Font _font;
        sf::Font font_2;
        sf::Texture _logoTexture;
        sf::Texture _createRoomTexture;
        sf::Texture _settingsTexture;
        sf::Sprite _logo;
        sf::Sprite _settings;
        sf::Sprite _validateButton;
        sf::RectangleShape _roomContainer;
        sf::RectangleShape _outerContainer;
        sf::Texture _backgroundTexture;
        sf::Sprite _background;

        sf::Text _playerNameText;
        sf::Text _playerText;
        std::string _playerName;
        std::string _createdRoom;
        Client &_client;
    };
} // namespace rtype

#endif /* !MENU_HPP_ */