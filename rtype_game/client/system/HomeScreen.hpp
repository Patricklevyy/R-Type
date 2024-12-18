#ifndef HOMESCREEN_HPP_
#define HOMESCREEN_HPP_

#include <SFML/Graphics.hpp>

namespace rtype {
    class HomeScreen {
    public:
        HomeScreen(int width, int height);
        ~HomeScreen() = default;

        void display(sf::RenderWindow &window);
        bool handleEvent(sf::Event &event, sf::RenderWindow &window);
        void resizeView(sf::RenderWindow &window); // Ajuste les éléments à la taille de l'écran

    private:
        int window_width;
        int window_height;

        sf::Font font;
        sf::Text playButtonText;

        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite;
        float normalSize;
        float hoverSize;  

        void setupButton();
    };
}

#endif /* HOMESCREEN_HPP_ */
