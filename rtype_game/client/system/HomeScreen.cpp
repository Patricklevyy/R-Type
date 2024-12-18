#include "HomeScreen.hpp"
#include <stdexcept>

namespace rtype {

    HomeScreen::HomeScreen(int width, int height)
    : window_width(width), window_height(height), normalSize(36), hoverSize(42) {

        if (!font.loadFromFile("assets/arial.ttf")) {
            throw std::runtime_error("Failed to load font.");
        }

        playButtonText.setFont(font);
        playButtonText.setString("Play Game");
        playButtonText.setCharacterSize(normalSize);
        playButtonText.setFillColor(sf::Color::White);
        playButtonText.setOrigin(playButtonText.getLocalBounds().width / 2,
                                playButtonText.getLocalBounds().height / 2);
        playButtonText.setPosition(window_width / 2, window_height / 2);

        if (!backgroundTexture.loadFromFile("assets/espace.jpg")) {
            throw std::runtime_error("Failed to load background texture.");
        }

        backgroundSprite.setTexture(backgroundTexture);

        float scaleX = static_cast<float>(window_width) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(window_height) / backgroundTexture.getSize().y;
        backgroundSprite.setScale(scaleX, scaleY);
    }



    void HomeScreen::display(sf::RenderWindow &window) {
        sf::View view(sf::FloatRect(0, 0, window_width, window_height));
        window.setView(view);

        window.clear();
        window.draw(backgroundSprite);
        window.draw(playButtonText);
        window.display();
    }


    bool HomeScreen::handleEvent(sf::Event &event, sf::RenderWindow &window) {
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
                return true;
            }
        }

        return false;
    }

    void HomeScreen::resizeBackground(sf::Vector2u newSize) {
        float scaleX = static_cast<float>(newSize.x) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(newSize.y) / backgroundTexture.getSize().y;

        backgroundSprite.setScale(scaleX, scaleY);

        backgroundSprite.setPosition(0, 0);

        window_width = newSize.x;
        window_height = newSize.y;

        playButtonText.setPosition(window_width / 2, window_height / 2);
    }


void HomeScreen::resizeView(sf::RenderWindow &window) {
        sf::Vector2u newSize = window.getSize();
        window_width = newSize.x;
        window_height = newSize.y;

        sf::View view(sf::FloatRect(0, 0, window_width, window_height));
        window.setView(view);

        resizeBackground(newSize);
    }
}
