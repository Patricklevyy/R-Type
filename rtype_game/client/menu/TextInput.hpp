/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

#ifndef TEXTINPUT_HPP_
#define TEXTINPUT_HPP_
#include <SFML/Graphics.hpp>

namespace rtype
{
    class TextInput {
      public:
        TextInput(sf::Font &font, sf::Vector2f position, sf::Vector2f size);
        ~TextInput() {};
        void draw(sf::RenderWindow &window);
        void handleEvent(const sf::Event &event);
        const std::string &getText() const;
        void setPosition(sf::Vector2f position);
        void clear();

      protected:
      private:
        sf::RectangleShape _shape;
        sf::Text _text;
        std::string _input;
        bool _isActive;
    };
} // namespace rtype

#endif /* !TEXTINPUT_HPP_ */
