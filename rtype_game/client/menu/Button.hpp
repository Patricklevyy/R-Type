/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Button
*/

#include <SFML/Graphics.hpp>

namespace rtype
{
    class Button {
      public:
        Button(const std::string &text, sf::Font &font, sf::Vector2f position,
            sf::Color color)
        {
            shape.setSize({200, 50});
            shape.setPosition(position);
            shape.setFillColor(color);

            buttonText.setFont(font);
            buttonText.setString(text);
            buttonText.setCharacterSize(24);
            buttonText.setFillColor(sf::Color::White);
            buttonText.setPosition(position.x
                    + (shape.getSize().x - buttonText.getGlobalBounds().width)
                        / 2,
                position.y
                    + (shape.getSize().y - buttonText.getGlobalBounds().height)
                        / 2
                    - 5);
        }

        void draw(sf::RenderWindow &window)
        {
            window.draw(shape);
            window.draw(buttonText);
        }

        bool isClicked(const sf::Vector2i &mousePos) const
        {
            return shape.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(mousePos));
        }

      private:
        sf::RectangleShape shape;
        sf::Text buttonText;
    };
} // namespace rtype