/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include <SFML/Graphics.hpp>
    #include <memory>
    #include <string>

    namespace rtype
    {
        class Text {
            public:
                Text(const std::string& text, const std::string& fontPath, unsigned int characterSize = 40, float x = 20, float y = 20)
                    : _font(std::make_shared<sf::Font>()), _text(std::make_shared<sf::Text>()) {
                    if (!_font->loadFromFile(fontPath)) {
                        throw std::runtime_error("Erreur: Impossible de charger la police à partir de " + fontPath);
                    }
                    _text->setFont(*_font);
                    _text->setString(text);
                    _text->setCharacterSize(characterSize);
                    _text->setFillColor(sf::Color::White);
                    _text->setPosition(x, y);
                }

                std::shared_ptr<sf::Text> getText() const {
                    return _text;
                }

                void setText(const std::string& newText) {
                    _text->setString(newText);
                }

                void setPosition(float x, float y) {
                    _text->setPosition(x, y);
                }

                void setColor(const sf::Color& color) {
                    _text->setFillColor(color);
                }

            private:
                std::shared_ptr<sf::Font> _font;
                std::shared_ptr<sf::Text> _text;
            };
    }

#endif /* !TEXT_HPP_ */
