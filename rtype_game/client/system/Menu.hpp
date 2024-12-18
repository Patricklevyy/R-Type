#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Audio.hpp>


namespace rtype {
    class Menu {
    public:
        Menu(int width, int height);
        ~Menu() = default;

        // Affiche le menu principal
        void display(sf::RenderWindow &window);
        bool handleEvent(sf::Event &event, sf::RenderWindow &window);

        // Nouvelle méthode pour afficher les rooms
        std::string displayRoomSelection(sf::RenderWindow &window, const std::vector<std::string> &rooms);
        bool handleRoomEvent(sf::Event &event, const std::vector<sf::Text> &roomTexts, int &selectedRoom);

    private:
        sf::View uiView;
        int window_width;
        int window_height;

        // Bouton principal Join Room
        sf::RectangleShape button;
        sf::Text buttonText;

        sf::Music backgroundMusic; // Ajout pour la musique

        // Background animé
        sf::Texture backgroundTexture;
        sf::Sprite backgroundSprite1;
        sf::Sprite backgroundSprite2;
        float scrollSpeed;

        // Texte pour afficher les rooms
        std::vector<sf::Text> roomTexts;
        int selectedRoomIndex;

        void setupButtons();

        sf::Font font;
        sf::Text joinRoomText;
        sf::Text optionsText;
        sf::Text createRoomText;
        sf::Text exitText;

        // Méthodes internes
        void updateBackground();
        void resizeBackground(sf::Vector2u newSize);
        void handleButtonHover(sf::Text &button, const sf::Vector2f &mousePos);
        void resizeView(sf::RenderWindow &window);

    };
}

#endif /* MENU_HPP_ */
