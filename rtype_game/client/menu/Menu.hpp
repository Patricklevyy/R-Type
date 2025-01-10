/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#ifndef MENU_HPP_
#define MENU_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include "Button.hpp"
#include "RoomHandling.hpp"
#include "TextInput.hpp"

namespace rtype
{

    class Menu {
      public:
        Menu(sf::Font &font);
        ~Menu() {};
        void draw(sf::RenderWindow &window);
        void handleClick(
            const sf::Vector2i &mousePos, const std::string &clientName);
        void handleEvent(const sf::Event &event);
        const std::string &getSelectedRoom() const;
        void addRoom(const std::string &name, int occupied);
        bool isCreatingRoom() const;
        const std::string &getRoomName() const;
        void clearRoomInput();
        void stopCreatingRoom();

      protected:
      private:
        sf::Font &font;
        Button joinButton;
        Button createButton;
        TextInput textInput;
        std::vector<std::shared_ptr<RoomHandling>> rooms;
        bool showRoomList;
        bool creatingRoom;
        std::string selectedRoom;
    };
} // namespace rtype

#endif /* !MENU_HPP_ */
