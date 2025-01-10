/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"

namespace rtype
{
    Menu::Menu(sf::Font &font)
        : font(font),
          joinButton("Join Room", font, {300, 200}, sf::Color::Blue),
          createButton("Create Room", font, {300, 300}, sf::Color::Green),
          textInput(font, {200, 400}), showRoomList(false), creatingRoom(false)
    {
    }

    void Menu::draw(sf::RenderWindow &window)
    {
        if (!showRoomList && !creatingRoom) {
            joinButton.draw(window);
            createButton.draw(window);
        } else if (creatingRoom) {
            textInput.draw(window);
        } else {
            for (const auto &room : rooms) {
                room->draw(window);
            }
        }
    }

    void Menu::handleClick(
        const sf::Vector2i &mousePos, const std::string &clientName)
    {
        if (!showRoomList && !creatingRoom) {
            if (joinButton.isClicked(mousePos)) {
                showRoomList = true;
            } else if (createButton.isClicked(mousePos)) {
                creatingRoom = true;
            }
        } else if (creatingRoom) {
            // Rien à faire ici
        } else {
            for (const auto &room : rooms) {
                if (room->isClicked(mousePos)) {
                    selectedRoom = room->getName();
                    // client.send_server_join_room(selectedRoom, clientName);
                    showRoomList = false;
                }
            }
        }
    }

    void Menu::handleEvent(const sf::Event &event)
    {
        // if (creatingRoom) {
        //     textInput.handleEvent(event);
        //     if (event.type == sf::Event::KeyPressed
        //         && event.key.code == sf::Keyboard::Enter) {
        //         std::string roomName = textInput.getText();

        //         // client.send_server_create_room(roomName); // Appel à la
        //         // fonction
        //         addRoom(roomName, 0);
        //         textInput.clear();
        //         creatingRoom = false;
        //     }
        // }
        if (creatingRoom) {
            textInput.handleEvent(event);
        }
    }

    void Menu::addRoom(const std::string &name, int occupied)
    {
        float yOffset = 100 + rooms.size() * 50;
        rooms.push_back(std::make_shared<RoomHandling>(
            name, occupied, font, sf::Vector2f(200, yOffset)));
    }

    const std::string &Menu::getSelectedRoom() const
    {
        return selectedRoom;
    }
    bool Menu::isCreatingRoom() const
    {
        return creatingRoom;
    }
    const std::string &Menu::getRoomName() const
    {
        std::cout << "getRoomName() called, returning: " << textInput.getText() << std::endl;
        return textInput.getText();
    }
    void Menu::clearRoomInput()
    {
        textInput.clear();
    }

    void Menu::stopCreatingRoom()
    {
        creatingRoom = false;
        textInput.clear();
    }
} // namespace rtype