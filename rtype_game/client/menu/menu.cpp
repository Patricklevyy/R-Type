#include "menu.hpp"
#include <iostream>

namespace rtype {
    Menu::Menu(int width, int height, const std::string &title)
    : _window(sf::VideoMode(width, height), title) {
    _window.setFramerateLimit(60);

    if (!_backgroundTexture.loadFromFile("rtype_game/client/menu/axel.png")) {
        throw std::runtime_error("Erreur : Impossible de charger le fichier");
    }

    _backgroundSprite.setTexture(_backgroundTexture);

    float scaleX = static_cast<float>(width) / _backgroundTexture.getSize().x;
    float scaleY = static_cast<float>(height) / _backgroundTexture.getSize().y;
    _backgroundSprite.setScale(scaleX, scaleY);
}


    void Menu::run() {
        while (_window.isOpen()) {
            handleEvents();
            render();
        }
    }

    void Menu::handleEvents() {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }
        }
    }

    void Menu::render() {
        _window.clear();
        _window.draw(_backgroundSprite);
        _window.display();
    }
}
