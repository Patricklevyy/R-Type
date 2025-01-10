/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** RoomHandling
*/

#ifndef ROOMHANDLING_HPP_
#define ROOMHANDLING_HPP_

#include <iostream>
#include <sstream>

namespace rtype
{
    class RoomHandling {
      public:
        RoomHandling(const std::string &name, int occupied, sf::Font &font,
            sf::Vector2f position)
            : name(name), occupied(occupied)
        {
            shape.setSize({400, 40});
            shape.setPosition(position);
            shape.setFillColor(sf::Color(200, 200, 200));

            std::ostringstream roomInfo;
            roomInfo << name << " (" << occupied << "/4)";
            roomText.setFont(font);
            roomText.setString(roomInfo.str());
            roomText.setCharacterSize(20);
            roomText.setFillColor(sf::Color::Black);
            roomText.setPosition(position.x + 10, position.y + 5);
        }

        ~RoomHandling() {};

        void draw(sf::RenderWindow &window)
        {
            window.draw(shape);
            window.draw(roomText);
        }

        bool isClicked(const sf::Vector2i &mousePos) const
        {
            return shape.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(mousePos));
        }

        const std::string &getName() const
        {
            return name;
        }

      protected:
      private:
        std::string name;
        int occupied;
        sf::RectangleShape shape;
        sf::Text roomText;
    };
} // namespace rtype

#endif /* !ROOMHANDLING_HPP_ */
