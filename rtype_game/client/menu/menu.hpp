#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <string>

namespace rtype {
    class Menu {
    public:
        Menu(int width, int height, const std::string &title);
        void run();

    private:
        void handleEvents();
        void render();
        void update(float deltaTime);

        // Nouvelle méthode pour centrer le texte
        void centerText(int characterSize = 0);

        sf::RenderWindow _window;
        sf::Texture _backgroundTexture;
        sf::Sprite _backgroundSprite;

        sf::Font _font;
        sf::Text _buttonText;

        float _scrollSpeed;
        float _offset;
    };
}

#endif // MENU_HPP
