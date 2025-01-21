/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** RoomHandling
*/

#ifndef ROOMHANDLING_HPP_
#define ROOMHANDLING_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <unordered_set>

namespace rtype
{
      /**
       * @class RoomHandling
       * @brief Manage the rooms (join, create).
       */
    class RoomHandling {
      public:

      /**
       * @brief Constructor for the RoomHandling class.
       * @param _font The font to use for the room name.
       * @param rooms All the rooms available.
       */
        RoomHandling(sf::Font &_font, std::vector<std::pair<std::string, int>> &rooms)
        : _rooms(rooms), _font(_font), _scrollOffset(0) {};

      /**
       * @brief Destructor for the RoomHandling class.
       */
        ~RoomHandling() {};

      /**
       * @brief Creation of a room.
       * @param name The name of the new room.
       * @param nb_places The places availables in the room.
       */
        void addRoom(const std::string &name, int nb_places)
        {
            _rooms.emplace_back(name, nb_places);
        }

      /**
       * @brief Handle when a client click on a room to join it.
       * @param mousePos The position of the mouse.
       * @param container The conatiner that conatin all the rooms.
       */
        std::string handleClick(
            const sf::Vector2f &mousePos, const sf::RectangleShape &container)
        {
            for (std::size_t i = 0; i < _rooms.size(); ++i) {
                float yPosition =
                    container.getPosition().y + 20 + i * 45 - _scrollOffset;
                sf::RectangleShape roomShape;
                roomShape.setSize({container.getSize().x - 40, 40});
                roomShape.setPosition(
                    {container.getPosition().x + 20, yPosition});
                if (roomShape.getGlobalBounds().contains(mousePos)) {
                    _selectedRoom = _rooms[i].first;
                    return _selectedRoom;
                }
            }
            _selectedRoom = "";
            return _selectedRoom;
        }

      /**
       * @brief Handle the scroll if there are too many rooms available.
       * @param delta The scroll.
       */
        void handleScroll(float delta)
        {
            _scrollOffset += delta * 20;
            if (_scrollOffset < 0)
                _scrollOffset = 0;
        }

      /**
       * @brief Draw the menu for the Rooms.
       * @param window The window in wich we want to display the Rooms menu.
       * @param container The container to display the rooms inside like a board.
       */
        void draw(sf::RenderWindow &window, const sf::RectangleShape &container)
        {
            std::unordered_set<std::string> drawnRooms;
            for (std::size_t i = 0; i < _rooms.size(); ++i) {
                if (drawnRooms.count(_rooms[i].first) > 0) {
                    continue;
                }
                float yPosition =
                    container.getPosition().y + 20 + i * 45 - _scrollOffset;
                if (yPosition >= container.getPosition().y
                    && yPosition
                        <= container.getPosition().y + container.getSize().y) {
                    sf::RectangleShape roomShape;
                    roomShape.setSize({container.getSize().x - 40, 40});
                    roomShape.setPosition(
                        {container.getPosition().x + 20, yPosition});
                    roomShape.setFillColor(sf::Color(30, 30, 30));
                    roomShape.setOutlineColor(sf::Color::White);
                    roomShape.setOutlineThickness(1);

                    sf::Text roomText;
                    roomText.setFont(_font);
                    roomText.setString(_rooms[i].first + " ("
                        + std::to_string(_rooms[i].second) + "/4)");
                    roomText.setCharacterSize(18);
                    roomText.setFillColor(sf::Color::White);
                    roomText.setPosition(roomShape.getPosition().x + 10,
                        roomShape.getPosition().y + 8);

                    window.draw(roomShape);
                    window.draw(roomText);
                    drawnRooms.insert(_rooms[i].first);
                }
            }
        }

      /**
       * @brief Get the room choosen by the player.
       */
        std::string getSelectedRoom() const
        {
            return _selectedRoom;
        }

        std::vector<std::pair<std::string, int>> &_rooms;

      protected:
      private:
        sf::Font &_font;
        float _scrollOffset;
        std::string _selectedRoom;
    };
} // namespace rtype

#endif /* !ROOMHANDLING_HPP_ */
