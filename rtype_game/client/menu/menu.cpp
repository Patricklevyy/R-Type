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
        centerText(_buttonText);
    }

    void Menu::initializeButtons() {
        std::vector<std::string> buttonLabels = {"CREATE ROOM", "JOIN ROOM", "OPTIONS", "EXIT"};
        float buttonY = 200.f;

        for (const auto &label : buttonLabels) {
            Button button;
            button.text.setFont(_font);
            button.text.setString(label);
            button.text.setCharacterSize(30);
            button.text.setFillColor(sf::Color::White);
            button.text.setPosition(_window.getSize().x / 2.f, buttonY);

            centerText(button.text);
            _buttons.push_back(button);

            buttonY += 80.f;
        }
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
                centerText(_buttonText);
                for (auto &button : _buttons) {
                    centerText(button.text);
                }
            }

            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

            if (!_showSecondaryMenu) {
                sf::FloatRect textBounds = _buttonText.getGlobalBounds();
                if (textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    _buttonText.setFillColor(sf::Color::Red);

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        _showSecondaryMenu = true;
                        initializeButtons();
                    }
                } else {
                    _buttonText.setFillColor(sf::Color::White);
                }
            } else {
                for (auto &button : _buttons) {
                    sf::FloatRect textBounds = button.text.getGlobalBounds();
                    if (textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                        button.text.setFillColor(sf::Color::Red);

                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                            if (button.text.getString() == "EXIT") {
                                _window.close();
                            } else {
                                std::cout << button.text.getString().toAnsiString() << " clicked!" << std::endl;
                            }
                        }
                    } else {
                        button.text.setFillColor(sf::Color::White);
                    }
                }
            }
        }
    }

    void Menu::render() {
        _window.clear();
        _window.draw(_backgroundSprite);

        if (!_showSecondaryMenu) {
            _window.draw(_buttonText);
        } else {
            for (const auto &button : _buttons) {
                _window.draw(button.text);
            }
        }

        _window.display();
    }

    void Menu::centerText(sf::Text &text, int characterSize) {
        if (characterSize > 0) {
            text.setCharacterSize(characterSize);
        }

        sf::FloatRect textBounds = text.getGlobalBounds();
        text.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
        text.setPosition(static_cast<float>(_window.getSize().x) / 2.f, text.getPosition().y);
    }
}
