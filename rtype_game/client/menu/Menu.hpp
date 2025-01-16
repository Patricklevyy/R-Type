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

namespace rtype
{
    class Client;
    class Menu {
      public:
        Menu(sf::RenderWindow &window, const std::string &name, Client &client);
        ~Menu() {};
        void run(bool &);
        void handleEvents(bool &_in_menu);
        void update();
        void render();
        std::string getPlayerName() const { return _playerName; }
        std::string getCreatedRoom() const { return _createdRoom; }
        std::shared_ptr<RoomHandling> _roomHandling;
        std::shared_ptr<TextInput> _textInput;
        void syncRooms();
        std::vector<std::pair<std::string, int>> roomsList;
        void joinRoomEvent();

      protected:
      private:
        sf::RenderWindow &_window;
        sf::Font _font;
        sf::Texture _logoTexture;
        sf::Texture _createRoomTexture;
        sf::Sprite _logo;
        sf::Sprite _validateButton;
        sf::RectangleShape _roomContainer;
        sf::RectangleShape _outerContainer;

        sf::Text _playerNameText;
        std::string _playerName;
        std::string _createdRoom;
        Client &_client;
    };
} // namespace rtype

#endif /* !MENU_HPP_ */
