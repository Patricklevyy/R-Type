#include "HomeScreen.hpp"
#include <stdexcept>

namespace rtype {

    HomeScreen::HomeScreen(int width, int height)
    : window_width(width), window_height(height), normalSize(36), hoverSize(42) {

    // Chargement de la police
    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font.");
    }

    // Texte du bouton "Play Game"
    playButtonText.setFont(font);
    playButtonText.setString("Play Game");
    playButtonText.setCharacterSize(normalSize);
    playButtonText.setFillColor(sf::Color::White);
    playButtonText.setOrigin(playButtonText.getGlobalBounds().width / 2,
                             playButtonText.getGlobalBounds().height / 2);
    playButtonText.setPosition(window_width / 2, window_height / 2);

    // Chargement du background
    if (!backgroundTexture.loadFromFile("assets/espace.jpg")) {
        throw std::runtime_error("Failed to load background texture.");
    }

    backgroundSprite.setTexture(backgroundTexture);

    // Ajuster le background à la taille initiale
    float scaleX = static_cast<float>(window_width) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window_height) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);
}


    void HomeScreen::display(sf::RenderWindow &window) {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(playButtonText);
        window.display();
    }

    bool HomeScreen::handleEvent(sf::Event &event, sf::RenderWindow &window) {
        // Gestion des événements
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2f mousePos(event.mouseMove.x, event.mouseMove.y);
            if (playButtonText.getGlobalBounds().contains(mousePos)) {
                playButtonText.setCharacterSize(hoverSize);
                playButtonText.setOrigin(playButtonText.getGlobalBounds().width / 2,
                                         playButtonText.getGlobalBounds().height / 2);
                playButtonText.setPosition(window_width / 2, window_height / 2);
            } else {
                playButtonText.setCharacterSize(normalSize);
                playButtonText.setOrigin(playButtonText.getGlobalBounds().width / 2,
                                         playButtonText.getGlobalBounds().height / 2);
                playButtonText.setPosition(window_width / 2, window_height / 2);
            }
        }

        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
            if (playButtonText.getGlobalBounds().contains(mousePos)) {
                return true; // Bouton "Play Game" cliqué
            }
        }

        return false;
    }

    void HomeScreen::resizeView(sf::RenderWindow &window) {
    sf::Vector2u size = window.getSize();
    window_width = size.x;
    window_height = size.y;

    // Redimensionner le background
    float scaleX = static_cast<float>(window_width) / backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(window_height) / backgroundTexture.getSize().y;
    backgroundSprite.setScale(scaleX, scaleY);

    // Recentre le bouton
    playButtonText.setPosition((window_width - playButtonText.getGlobalBounds().width) / 2,
                               (window_height - playButtonText.getGlobalBounds().height) / 2);
}

}
