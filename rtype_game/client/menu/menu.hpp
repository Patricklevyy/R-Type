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

        sf::RenderWindow _window;
        sf::Texture _backgroundTexture;
        sf::Sprite _backgroundSprite;
    };
}

#endif // MENU_HPP
