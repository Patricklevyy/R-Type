/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Text
*/

/**
 * @file Text.hpp
 * @brief Header file for the Text class.
 */


#ifndef TEXT_HPP_
    #define TEXT_HPP_

    #include <SFML/Graphics.hpp>
    #include <memory>
    #include <string>

    namespace rtype
    {
        /**
         * @brief A class to manage and render text using SFML.
         * 
         * This class provides a simplified interface to handle text rendering
         * in a 2D game context. It uses shared pointers for `sf::Font` and `sf::Text`
         * to manage resources efficiently.
         */
        class Text {
            public:
                /**
                 * @brief Constructs a new Text object.
                 * 
                 * Initializes the text with a specified string, font, character size, and position.
                 * Throws a runtime exception if the font file cannot be loaded.
                 * 
                 * @param text The string to display.
                 * @param fontPath The file path to the font to use.
                 * @param characterSize The size of the characters. Default is 40.
                 * @param x The x-coordinate of the text position. Default is 20.
                 * @param y The y-coordinate of the text position. Default is 20.
                 * 
                 * @throws std::runtime_error If the font file cannot be loaded.
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
                 * @brief Retrieves the `sf::Text` object for rendering or modification.
                 * 
                 * @return A shared pointer to the `sf::Text` object.
                 */
                std::shared_ptr<sf::Text> getText() const {
                    return _text;
                }

                /**
                 * @brief Updates the displayed text string.
                 * 
                 * Changes the text content that is being rendered.
                 * 
                 * @param newText The new string to display.
                 */
                void setText(const std::string& newText) {
                    _text->setString(newText);
                }

                /**
                 * @brief Sets the position of the text on the screen.
                 * 
                 * Updates the text's x and y position in 2D space.
                 * 
                 * @param x The new x-coordinate of the text position.
                 * @param y The new y-coordinate of the text position.
                 */
                void setPosition(float x, float y) {
                    _text->setPosition(x, y);
                }

                /**
                 * @brief Sets the color of the text.
                 * 
                 * Changes the fill color of the text.
                 * 
                 * @param color The new color to set.
                 */
                void setColor(const sf::Color& color) {
                    _text->setFillColor(color);
                }

            private:
                std::shared_ptr<sf::Font> _font; ///< Shared pointer to the font used for the text.
                std::shared_ptr<sf::Text> _text; ///< Shared pointer to the SFML text object.
            };
    }

#endif /* !TEXT_HPP_ */
