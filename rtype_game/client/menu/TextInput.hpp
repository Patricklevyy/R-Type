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
    /**
     * @class TextInput
     * @brief Handle the texts enter by the user.
     */
    class TextInput {
      public:
      /**
       * @brief The constructor for the TextInput class.
       * @param font The font to use for the text when displayed.
       * @param position Where to draw the text.
       * @param size The size of the text.
       */
        TextInput(sf::Font &font, sf::Vector2f position, sf::Vector2f size);

      /**
       * @brief The destructor for the TextInput class.
       */
        ~TextInput() {};

      /**
       * @brief Draw the text enter by the user.
       * @param window The window to display the text.
       */
        void draw(sf::RenderWindow &window);

      /**
       * @brief Handle the events made by the user.
       * @param event The actions made by the user
       */
        void handleEvent(const sf::Event &event);

      /**
       * @brief Get the text enter by a player.
       */
        const std::string &getText() const;

      /**
       * @brief Set the position of the text.
       * @param position The postion of the text
       */
        void setPosition(sf::Vector2f position);

      /**
       * @brief Remove text for the screen.
       */
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
