/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

#include "TextInput.hpp"

namespace rtype
{
    TextInput::TextInput(
        sf::Font &font, sf::Vector2f position, sf::Vector2f size)
        : _isActive(false)
    {
        _shape.setSize(size);
        _shape.setPosition(position);
        _shape.setFillColor(sf::Color::White);
        _shape.setOutlineColor(sf::Color::Black);
        _shape.setOutlineThickness(2);

        _text.setFont(font);
        _text.setCharacterSize(18);
        _text.setFillColor(sf::Color::Black);
        _text.setPosition(position.x + 10, position.y + 8);
    }

    void TextInput::draw(sf::RenderWindow &window)
    {
        window.draw(_shape);
        window.draw(_text);
    }

    void TextInput::handleEvent(const sf::Event &event)
    {
        if (event.type == sf::Event::MouseButtonPressed
            && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
            _isActive = _shape.getGlobalBounds().contains(
                static_cast<sf::Vector2f>(mousePos));
        }

        if (_isActive && event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && !_input.empty()) {
                _input.pop_back();
            } else if (event.text.unicode < 128 && event.text.unicode != '\b'
                && event.text.unicode != '\r') {
                _input += static_cast<char>(event.text.unicode);
            }
            _text.setString(_input);
        }
    }

    const std::string &TextInput::getText() const
    {
        return _input;
    }

    void TextInput::clear()
    {
        _input.clear();
        _text.setString("");
    }

    void TextInput::setPosition(sf::Vector2f position)
    {
        _shape.setPosition(position);
        _text.setPosition(position.x + 10, position.y + 8);
    }
} // namespace rtype