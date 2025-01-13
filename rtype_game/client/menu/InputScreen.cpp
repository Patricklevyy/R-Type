/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** InputScreen
*/

#include "InputScreen.hpp"

namespace rtype
{
    InputScreen::InputScreen(sf::RenderWindow &win) : _window(win)
    {
        if (!_font.loadFromFile("assets/fonts/komikax.ttf")) {
            throw std::runtime_error("Erreur de chargement de la police");
        }
        if (!_font_2.loadFromFile("assets/fonts/Georgia Regular font.ttf")) {
            throw std::runtime_error("Erreur de chargement de la police");
        }
        if (!_logoTexture.loadFromFile("assets/backgrounds/logo.png")) {
            throw std::runtime_error("Erreur de chargement de l'image du logo");
        }
        if (!_validateTexture.loadFromFile(
                "assets/backgrounds/validate_button.png")) {
            throw std::runtime_error(
                "Erreur de chargement de l'image du bouton");
        }

        _title.setFont(_font);
        _title.setString("ENTER YOUR NAME");
        _title.setCharacterSize(30);
        _title.setFillColor(sf::Color::White);
        _title.setStyle(sf::Text::Bold | sf::Text::Underlined);

        _logo.setTexture(_logoTexture);
        _logo.setScale(0.3f, 0.3f);

        _inputBox.setSize(sf::Vector2f(300.f, 50.f));
        _inputBox.setFillColor(sf::Color(20, 20, 20));
        _inputBox.setOutlineThickness(2.f);
        _inputBox.setOutlineColor(sf::Color::Cyan);

        _userInput.setFont(_font_2);
        _userInput.setCharacterSize(20);
        _userInput.setFillColor(sf::Color::White);

        _validateButton.setTexture(_validateTexture);
        _validateButton.setScale(0.35f, 0.35f);
    }

    void InputScreen::run(bool &isRunning, std::string &playerName)
    {
        while (_window.isOpen() && isRunning) {
            sf::Event event;

            while (_window.pollEvent(event)) {
                handleEvent(event, isRunning, playerName);
            }
            update();
            _window.clear(sf::Color(10, 10, 40));
            render();
            _window.display();
        }
    }

    void InputScreen::handleEvent(
        sf::Event &event, bool &isRunning, std::string &playerName)
    {
        if (event.type == sf::Event::Closed) {
            isRunning = false;
            _window.close();
        }
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == '\b' && !_inputString.empty()) {
                _inputString.pop_back();
            } else if (event.text.unicode < 128 && event.text.unicode != '\b') {
                _inputString += static_cast<char>(event.text.unicode);
            }
            _userInput.setString(_inputString);
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

            if (_validateButton.getGlobalBounds().contains(
                    mousePos.x, mousePos.y)) {
                _isButtonPressed = true;
                _validateButton.setScale(0.33f, 0.33f);
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (_isButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

                if (_validateButton.getGlobalBounds().contains(
                        mousePos.x, mousePos.y)) {
                    playerName = _inputString;
                    isRunning = false; // Quitte cet écran
                }
                _isButtonPressed = false;
                _validateButton.setScale(0.35f, 0.35f);
            }
        }
    }

    void InputScreen::update()
    {
        if (!_window.isOpen()) {
            std::cerr << "Erreur : la fenêtre n'est pas valide ou est fermée."
                      << std::endl;
            return;
        }

        // sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

        // Effet de survol
        // if (_validateButton.getGlobalBounds().contains(
        //         mousePos.x, mousePos.y)) {
        //     if (!_isHovering) {
        //         _isHovering = true;
        //         _validateButton.setScale(0.37f, 0.37f);
        //     }
        // } else {
        //     if (_isHovering) {
        //         _isHovering = false;
        //         _validateButton.setScale(0.35f, 0.35f);
        //     }
        // }

        sf::Vector2u winSize = _window.getSize();

        _title.setPosition(
            (winSize.x - _title.getLocalBounds().width) / 2, 280);
        _logo.setPosition((winSize.x - _logo.getGlobalBounds().width) / 2, 20);
        _inputBox.setPosition(
            (winSize.x - _inputBox.getSize().x) / 2, winSize.y / 2 + 50);
        _userInput.setPosition(
            _inputBox.getPosition().x + 10, _inputBox.getPosition().y + 10);
        _validateButton.setPosition(
            (winSize.x - _validateButton.getGlobalBounds().width) / 2,
            _inputBox.getPosition().y + _inputBox.getSize().y + 20);
    }

    void InputScreen::render()
    {
        _window.draw(_title);
        _window.draw(_logo);
        _window.draw(_inputBox);
        _window.draw(_userInput);
        _window.draw(_validateButton);
    }
} // namespace rtype
