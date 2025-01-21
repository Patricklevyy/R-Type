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
        /**
         * @class Text
         * @brief The text that will be displayed in the game to give some informations such as menu or score.
         */
        class Text {
            public:
                /**
                 * @brief Constructor for the Text class.
                 * @param text The text to display.
                 * @param fontPath The path to the font to use in ttf.
                 * @param characterSize The size of the text to display.
                 * @param x The position of the text in x axe.
                 * @param y The position of the text in y axe.
                 */
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

                /**
                 * @brief Get the text to display.
                 */
                std::shared_ptr<sf::Text> getText() const {
                    return _text;
                }

                /**
                 * @brief Set the text to display.
                 */
                void setText(const std::string& newText) {
                    _text->setString(newText);
                }

                /**
                 * @brief Set the position of the text to display.
                 * @param x The position in x axe of the text.
                 * @param y The position in y axe of the text.
                 */
                void setPosition(float x, float y) {
                    _text->setPosition(x, y);
                }

                /**
                 * @brief Set the color of the text to display.
                 * @param color The color of the text.
                 */
                void setColor(const sf::Color& color) {
                    _text->setFillColor(color);
                }

            private:
                std::shared_ptr<sf::Font> _font;
                std::shared_ptr<sf::Text> _text;
            };
    }

#endif /* !TEXT_HPP_ */
