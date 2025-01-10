/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

#include "TextInput.hpp"

namespace rtype
{
    TextInput::TextInput(sf::Font &font, sf::Vector2f position)
        : isActive(false)
    {
        shape.setSize({400, 50});
        shape.setPosition(position);
        shape.setFillColor(sf::Color::White);
        shape.setOutlineColor(sf::Color::Black);
        shape.setOutlineThickness(2);

        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Black);
        text.setPosition(position.x + 10, position.y + 10);
    }

    void TextInput::draw(sf::RenderWindow &window)
    {
        window.draw(shape);
        window.draw(text);
    }

    void TextInput::handleEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonPressed
            && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            isActive = shape.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(mousePos));
        }

        if (isActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b') {
                if (!input.empty()) {
                    input.pop_back();
                }
            } else if (event.text.unicode == '\r') {
                isActive = false;
            } else if (event.text.unicode
                < 128) {
                input += static_cast<char>(event.text.unicode);
            }
            text.setString(input);
        }
    }

    const std::string &TextInput::getText() const
    {
        return input;
    }

    void TextInput::clear()
    {
        input.clear();
        text.setString("");
    }
} // namespace rtype