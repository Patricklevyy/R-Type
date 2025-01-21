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
     * @brief Menu of the project.
     */
    class Menu {
      public:
      /**
       * @brief Constructor of the Menu class.
       * @param window The window in wich the menu will be displayed.
       * @param name The name of the window.
       * @param client The client that is in the menu.
       */
        Menu(sf::RenderWindow &window, const std::string &name, Client &client);

      /**
       * @brief Destructor of the Menu class.
       */
        ~Menu() {};

      /**
       * @brief Handle the menu run, and all the events done on it.
       */
        void run(bool &);

      /**
       * @brief Handle events that are made in the menu.
       * @param _in_menu A boolean that states if the menu is active or not
       */
        void handleEvents(bool &_in_menu);

      /**
       * @brief Update the menu display and the menu Events.
       */
        void update();

      /**
       * @brief Render the Menu.
       */
        void render();

      /**
       * @brief Get the name of the player.
       */
        std::string getPlayerName() const { return _playerName; }

      /**
       * @brief Get all the room already created.
       */
        std::string getCreatedRoom() const { return _createdRoom; }

        std::shared_ptr<RoomHandling> _roomHandling;
        std::shared_ptr<TextInput> _textInput;

      /**
       * @brief Synchronise the room to stay coherent in all client.
       */
        void syncRooms();
        std::vector<std::pair<std::string, int>> roomsList;

      /**
       * @brief Client join a room form the menu.
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
