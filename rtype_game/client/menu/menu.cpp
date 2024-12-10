#include "menu.hpp"
#include <iostream>

namespace rtype {
    Menu::Menu(int width, int height, const std::string &title)
        : _window(sf::VideoMode(width, height), title), _scrollSpeed(50.0f), _offset(0.0f) {
        _window.setFramerateLimit(60);

        if (!_backgroundTexture.loadFromFile("rtype_game/client/menu/espace.jpeg")) {
            throw std::runtime_error("Erreur : Impossible de charger le fichier");
        }

        _backgroundTexture.setRepeated(true);
        _backgroundSprite.setTexture(_backgroundTexture);
        _backgroundSprite.setTextureRect(sf::IntRect(0, 0, width, height));

        if (!_font.loadFromFile("rtype_game/client/menu/arial.ttf")) {
            throw std::runtime_error("Erreur : Impossible de charger la police");
        }

        _buttonText.setFont(_font);
        _buttonText.setString("START GAME");
        _buttonText.setCharacterSize(30);
        _buttonText.setFillColor(sf::Color::White);
        centerText();
    }

    void Menu::update(float deltaTime) {
        _offset += _scrollSpeed * deltaTime;
        _backgroundSprite.setTextureRect(sf::IntRect(_offset, 0, _window.getSize().x, _window.getSize().y));
    }

    void Menu::run() {
        sf::Clock clock;

        while (_window.isOpen()) {
            float deltaTime = clock.restart().asSeconds();

            handleEvents();
            update(deltaTime);
            render();
        }
    }

    void Menu::handleEvents() {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }

            if (event.type == sf::Event::Resized) {
                _window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
                centerText();
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            sf::FloatRect textBounds = _buttonText.getGlobalBounds();

            if (textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                _buttonText.setFillColor(sf::Color::Red);
                _buttonText.setCharacterSize(35);
                centerText(35);
            } else {
                _buttonText.setFillColor(sf::Color::White);
                _buttonText.setCharacterSize(30);
                centerText();
            }
        }
    }

    void Menu::render() {
        _window.clear();
        _window.draw(_backgroundSprite);
        _window.draw(_buttonText);
        _window.display();
    }

    void Menu::centerText(int characterSize) {
        if (characterSize > 0) {
            _buttonText.setCharacterSize(characterSize);
        }

        sf::FloatRect textBounds = _buttonText.getGlobalBounds();
        float windowWidth = static_cast<float>(_window.getSize().x);
        float windowHeight = static_cast<float>(_window.getSize().y);

        _buttonText.setPosition(
            windowWidth / 2.f - textBounds.width / 2.f,
            windowHeight / 2.f - textBounds.height / 2.f
        );
    }
}
