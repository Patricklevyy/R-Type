#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

namespace rtype {
    class Menu {
    public:
        Menu(int width, int height, const std::string &title);
        void run();

    private:
        struct Button {
            sf::Text text;
        };

        void handleEvents();
        void render();
        void update(float deltaTime);
        void centerText(sf::Text &text, int characterSize = 0);

        void initializeButtons();

        sf::RenderWindow _window;
        sf::Texture _backgroundTexture;
        sf::Sprite _backgroundSprite;

        sf::Font _font;
        sf::Text _buttonText;

        float _scrollSpeed;
        float _offset;

        std::vector<Button> _buttons;
        bool _showSecondaryMenu = false;
    };
}

#endif // MENU_HPP

