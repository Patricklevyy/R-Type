#include "Menu.hpp"
#include <stdexcept>

namespace rtype {

    Menu::Menu(int width, int height)
        : window_width(width), window_height(height), scrollSpeed(1.0f) {

        if (!font.loadFromFile("assets/arial.ttf")) {
            throw std::runtime_error("Failed to load font.");
        }

        button.setSize(sf::Vector2f(200, 60));
        button.setFillColor(sf::Color::Red);
        button.setPosition((window_width - 200) / 2, (window_height - 60) / 2);

        buttonText.setFont(font);
        buttonText.setString("Join Room");
        buttonText.setCharacterSize(24);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setPosition(button.getPosition().x + 35, button.getPosition().y + 15);

        uiView.setSize(static_cast<float>(window_width), static_cast<float>(window_height));
        uiView.setCenter(window_width / 2.0f, window_height / 2.0f);

        if (!backgroundTexture.loadFromFile("assets/espace.jpg")) {
            throw std::runtime_error("Failed to load background texture.");
        }


        float scaleX = static_cast<float>(window_width) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(window_height) / backgroundTexture.getSize().y;

        backgroundSprite1.setScale(scaleX, scaleY);
        backgroundSprite2.setScale(scaleX, scaleY);


        backgroundSprite1.setTexture(backgroundTexture);
        backgroundSprite2.setTexture(backgroundTexture);

        backgroundSprite1.setPosition(0, 0);
        backgroundSprite2.setPosition(0, -window_height);
        setupButtons();

        if (!backgroundMusic.openFromFile("assets/espace.ogg")) {
        throw std::runtime_error("Failed to load background music.");
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(50);
    backgroundMusic.play();
    }

    void Menu::resizeView(sf::RenderWindow &window) {
        sf::Vector2u newSize = window.getSize();
        uiView.setSize(static_cast<float>(newSize.x), static_cast<float>(newSize.y));
        uiView.setCenter(newSize.x / 2.0f, newSize.y / 2.0f);
    }

    void Menu::setupButtons() {
        std::vector<sf::Text*> buttons = {&joinRoomText, &optionsText, &createRoomText, &exitText};
        std::vector<std::string> labels = {"Join Room", "Options", "Create Room", "Exit"};

        for (size_t i = 0; i < buttons.size(); ++i) {
            buttons[i]->setFont(font);
            buttons[i]->setString(labels[i]);
            buttons[i]->setCharacterSize(30);
            buttons[i]->setFillColor(sf::Color::White);
            buttons[i]->setPosition((window_width - 200) / 2, 300 + i * 70);
        }
    }

void Menu::handleButtonHover(sf::Text &button, const sf::Vector2f &mousePos) {
        if (button.getGlobalBounds().contains(mousePos)) {
            button.setCharacterSize(40);
        } else {
            button.setCharacterSize(30);
        }
    }


    void Menu::updateBackground() {
        float deltaTime = 0.016f;

        backgroundSprite1.move(0, scrollSpeed * deltaTime);
        backgroundSprite2.move(0, scrollSpeed * deltaTime);

        if (backgroundSprite1.getPosition().y >= window_height) {
            backgroundSprite1.setPosition(0, backgroundSprite2.getPosition().y - window_height);
        }
        if (backgroundSprite2.getPosition().y >= window_height) {
            backgroundSprite2.setPosition(0, backgroundSprite1.getPosition().y - window_height);
        }
    }


    void Menu::resizeBackground(sf::Vector2u newSize) {
        float scaleX = static_cast<float>(newSize.x) / backgroundTexture.getSize().x;
        float scaleY = static_cast<float>(newSize.y) / backgroundTexture.getSize().y;

        backgroundSprite1.setScale(scaleX, scaleY);
        backgroundSprite2.setScale(scaleX, scaleY);

        backgroundSprite1.setPosition(0, 0);
        backgroundSprite2.setPosition(0, -static_cast<float>(newSize.y));

        window_width = newSize.x;
        window_height = newSize.y;
    }


    void Menu::display(sf::RenderWindow &window) {
        updateBackground();

        window.setView(uiView);

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), uiView);
        handleButtonHover(joinRoomText, mousePos);
        handleButtonHover(optionsText, mousePos);
        handleButtonHover(createRoomText, mousePos);
        handleButtonHover(exitText, mousePos);

        window.clear();
        window.draw(backgroundSprite1);
        window.draw(backgroundSprite2);

        window.draw(joinRoomText);
        window.draw(optionsText);
        window.draw(createRoomText);
        window.draw(exitText);

        window.display();
    }



    bool Menu::handleEvent(sf::Event &event, sf::RenderWindow &window) {

        if (event.type == sf::Event::Resized) {
            resizeBackground(window.getSize());
            resizeView(window);
        }
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window), uiView);

            if (joinRoomText.getGlobalBounds().contains(mousePos)) {
                return true;
            }
            if (optionsText.getGlobalBounds().contains(mousePos)) {
                std::cout << "Options clicked!" << std::endl;
            }
            if (createRoomText.getGlobalBounds().contains(mousePos)) {
                std::cout << "Create Room clicked!" << std::endl;
            }
            if (exitText.getGlobalBounds().contains(mousePos)) {
                window.close();
            }
        }
        if (event.type == sf::Event::Resized) {
            resizeView(window);
        }
        return false;
    }
}
