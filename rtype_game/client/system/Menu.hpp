#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>
#include "../Client.hpp"


namespace rtype {
    class Menu {
    public:
        Menu(int width, int height);
        ~Menu() = default;

        void display(sf::RenderWindow &window);
        bool handleEvent(sf::Event &event, sf::RenderWindow &window);

        std::string displayRoomSelection(sf::RenderWindow &window, const std::vector<std::string> &rooms);
        bool handleRoomEvent(sf::Event &event, const std::vector<sf::Text> &roomTexts, int &selectedRoom);

    private:
        sf::View uiView;
        int window_width;
        int window_height;

        sf::RectangleShape button;
        sf::Text buttonText;

        sf::Music backgroundMusic;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite1;
        sf::Sprite backgroundSprite2;
        float scrollSpeed;

        std::vector<sf::Text> roomTexts;
        int selectedRoomIndex;

        void setupButtons();

        sf::Font font;
        sf::Text joinRoomText;
        sf::Text optionsText;
        sf::Text createRoomText;
        sf::Text exitText;

        void updateBackground();
        void resizeBackground(sf::Vector2u newSize);
        void handleButtonHover(sf::Text &button, const sf::Vector2f &mousePos);
        void resizeView(sf::RenderWindow &window);

    };
}

#endif /* MENU_HPP_ */
