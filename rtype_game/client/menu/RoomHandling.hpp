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

namespace rtype
{
    class RoomHandling {
      public:
        RoomHandling(
            sf::Font &_font,  std::vector<std::pair<std::string, int>> &rooms)
            : _font(_font), _scrollOffset(0), _rooms(rooms) {};
        ~RoomHandling() {};

        void addRoom(const std::string &name, int nb_places)
        {
            _rooms.emplace_back(name, nb_places);
        }

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

        void handleScroll(float delta)
        {
            _scrollOffset += delta * 20;
            if (_scrollOffset < 0)
                _scrollOffset = 0;
        }

        void draw(sf::RenderWindow &window, const sf::RectangleShape &container)
        {
            for (std::size_t i = 0; i < _rooms.size(); ++i) {
                // std::cout << "when drawing->" << _rooms[i].first << "->" << _rooms[i].second << std::endl;
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
                }
            }
        }

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
