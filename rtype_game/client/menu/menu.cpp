#include "menu.hpp"
#include <iostream>

namespace rtype {
    Menu::Menu(int width, int height, const std::string &title)
        : _window(sf::VideoMode(width, height), title), _scrollSpeed(50.0f), _offset(0.0f) {
        _window.setFramerateLimit(60);

        if (!_backgroundTexture.loadFromFile("rtype_game/client/menu/assets/espace.jpeg")) {
            throw std::runtime_error("Erreur : Impossible de charger le fichier");
        }

        _backgroundTexture.setRepeated(true);
        _backgroundSprite.setTexture(_backgroundTexture);
        _backgroundSprite.setTextureRect(sf::IntRect(0, 0, width, height));

        if (!_font.loadFromFile("rtype_game/client/menu/assets/arial.ttf")) {
            throw std::runtime_error("Erreur : Impossible de charger la police");
        }

        _buttonText.setFont(_font);
        _buttonText.setString("START GAME");
        _buttonText.setCharacterSize(30);
        _buttonText.setFillColor(sf::Color::White);

        _colorModeText.setFont(_font);
        _colorModeText.setCharacterSize(20);
        _colorModeText.setFillColor(sf::Color::White);
        _colorModeText.setPosition(10.f, 10.f);


        sf::Vector2u windowSize = _window.getSize();
        _buttonText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
        centerText(_buttonText);


        if (!_backgroundMusic.openFromFile("rtype_game/client/menu/assets/espace.ogg")) {
            throw std::runtime_error("Erreur : Impossible de charger la musique");
        }
        _backgroundMusic.setLoop(true);
    }

    void Menu::initializeButtons() {
        std::vector<std::string> buttonLabels = {"CREATE ROOM", "JOIN ROOM", "OPTIONS", "EXIT"};
        float buttonY = 200.f;

        for (const auto &label : buttonLabels) {
            Button button;
            button.text.setFont(_font);
            button.text.setString(label);
            button.text.setCharacterSize(50);
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

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::A) {
                switch (_currentColorMode) {
                    case ColorMode::Normal:
                        _currentColorMode = ColorMode::Deuteranopia;
                        break;
                    case ColorMode::Deuteranopia:
                        _currentColorMode = ColorMode::Protanopia;
                        break;
                    case ColorMode::Protanopia:
                        _currentColorMode = ColorMode::Deuteranomaly;
                        break;
                    case ColorMode::Deuteranomaly:
                        _currentColorMode = ColorMode::Protanomaly;
                        break;
                    case ColorMode::Protanomaly:
                        _currentColorMode = ColorMode::Tritanopia;
                        break;
                    case ColorMode::Tritanopia:
                        _currentColorMode = ColorMode::Tritanomaly;
                        break;
                    case ColorMode::Tritanomaly:
                        _currentColorMode = ColorMode::Achromatopsia;
                        break;
                    case ColorMode::Achromatopsia:
                        _currentColorMode = ColorMode::Normal;
                        break;
                }
                applyColorMode();
            }


            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

            if (!_showSecondaryMenu) {
                sf::FloatRect textBounds = _buttonText.getGlobalBounds();
                if (textBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
                    _buttonText.setFillColor(sf::Color::Red);

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        _showSecondaryMenu = true;
                        initializeButtons();

                        if (!_isMusicPlaying) {
                            _backgroundMusic.play();
                            _isMusicPlaying = true;
                        }
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

    void Menu::applyColorMode() {
        std::string modeName;

        switch (_currentColorMode) {
            case ColorMode::Normal:
                modeName = "Normal";
                _backgroundSprite.setColor(sf::Color::White);
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color::White);
                }
                break;

            case ColorMode::Deuteranopia:
                modeName = "Deuteranopia";
                _backgroundSprite.setColor(sf::Color(255, 255, 150));
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color(255, 255, 150));
                }
                break;

            case ColorMode::Protanopia:
                modeName = "Protanopia";
                _backgroundSprite.setColor(sf::Color(150, 255, 255));
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color(150, 255, 255));
                }
                break;

            case ColorMode::Deuteranomaly:
                modeName = "Deuteranomaly";
                _backgroundSprite.setColor(sf::Color(200, 255, 200));
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color(200, 255, 200));
                }
                break;

            case ColorMode::Protanomaly:
                modeName = "Protanomaly";
                _backgroundSprite.setColor(sf::Color(255, 200, 200));
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color(255, 200, 200));
                }
                break;

            case ColorMode::Tritanopia:
                modeName = "Tritanopia";
                _backgroundSprite.setColor(sf::Color(200, 200, 255));
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color(200, 200, 255));
                }
                break;

            case ColorMode::Tritanomaly:
                modeName = "Tritanomaly";
                _backgroundSprite.setColor(sf::Color(200, 255, 255));
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color(200, 255, 255));
                }
                break;

            case ColorMode::Achromatopsia:
                modeName = "Achromatopsia";
                _backgroundSprite.setColor(sf::Color(128, 128, 128));
                for (auto &button : _buttons) {
                    button.text.setFillColor(sf::Color(128, 128, 128));
                }
                break;
        }

        _colorModeText.setString("Color Mode: " + modeName);
        _showColorModeText = true;
        _colorModeClock.restart();
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

        if (_showColorModeText && _colorModeClock.getElapsedTime().asSeconds() <= 2.f) {
            _window.draw(_colorModeText);
        } else {
            _showColorModeText = false;
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
