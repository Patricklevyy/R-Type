/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

/**
 * @file TextInput.hpp
 * @brief Header file for the TextInput class.
 *
 * This file contains the declaration of the TextInput class that handles the creation
 * and interaction with a text input field in the game interface.
 */

#ifndef TEXTINPUT_HPP_
#define TEXTINPUT_HPP_

#include <SFML/Graphics.hpp>

namespace rtype
{
    /**
     * @class TextInput
     * @brief A class to manage user text input in the form of a text field.
     *
     * This class allows the user to enter text through an input box rendered in 
     * a window. It includes functionality for drawing the input box, processing 
     * text input, and modifying or clearing the entered text.
     */
    class TextInput {
      public:
        /**
         * @brief Construct a new TextInput object.
         * 
         * Initializes a text input field with specified font, position, and size.
         * 
         * @param font The font to be used for the text.
         * @param position The position of the text input field within the window.
         * @param size The size of the text input field.
         */
        TextInput(sf::Font &font, sf::Vector2f position, sf::Vector2f size);

        /**
         * @brief Destroy the TextInput object.
         */
        ~TextInput() {};

        /**
         * @brief Draw the text input field and its current text to the window.
         * 
         * This method renders the input field as well as the text the user has entered
         * onto the provided SFML window.
         * 
         * @param window The window in which the text input and text are to be drawn.
         */
        void draw(sf::RenderWindow &window);

        /**
         * @brief Handle events from the window.
         * 
         * Responds to events such as text input and modifies the input string
         * accordingly (e.g., handling backspace, character input, etc.).
         * 
         * @param event The event to handle, usually a key press or text entry.
         */
        void handleEvent(const sf::Event &event);

        /**
         * @brief Get the current entered text in the text input field.
         * 
         * Returns the text that the user has typed into the input field.
         * 
         * @return The string representing the input text.
         */
        const std::string &getText() const;

        /**
         * @brief Set the position of the text input field.
         * 
         * This method allows setting a new position for the text input box within the window.
         * 
         * @param position The new position of the text input field.
         */
        void setPosition(sf::Vector2f position);

        /**
         * @brief Clear the text input field.
         * 
         * Resets the entered text to an empty string.
         */
        void clear();

      protected:
      private:
        sf::RectangleShape _shape; ///< Rectangle shape representing the text input field.
        sf::Text _text; ///< SFML Text object to display the text entered by the user.
        std::string _input; ///< The string to store the current input text.
        bool _isActive; ///< Flag to indicate whether the text input is currently active.
    };
} // namespace rtype

#endif /* !TEXTINPUT_HPP_ */
