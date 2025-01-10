/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** TextInput
*/

#ifndef TEXTINPUT_HPP_
#define TEXTINPUT_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>


namespace rtype {
    class TextInput {
        public:
            TextInput(sf::Font &font, sf::Vector2f position);
            ~TextInput() {};
            void draw(sf::RenderWindow &window);
            void handleEvent(const sf::Event &event);
            const std::string &getText() const;
            void clear();

        protected:
        private:
            sf::RectangleShape shape;
            sf::Text text;
            std::string input;
            bool isActive;
    };
}
#endif /* !TEXTINPUT_HPP_ */
