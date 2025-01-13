/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Menu
*/

#include "Menu.hpp"
namespace rtype
{
    Menu::Menu(sf::RenderWindow &win, const std::string &name, Client &client)
        : _window(win), _playerName(name), _createdRoom(""), _client(client)
    {
        if (!_font.loadFromFile("Menu/Georgia Regular font.ttf")
            || !_logoTexture.loadFromFile("assets/backgrounds/logo.png")
            || !_createRoomTexture.loadFromFile(
                "assets/backgrounds/create_room_button.png")) {
            throw std::runtime_error("Failed to load resources");
        }

        _logo.setTexture(_logoTexture);
        _logo.setScale(0.3f, 0.3f);

        _validateButton.setTexture(_createRoomTexture);
        _validateButton.setScale(0.3f, 0.3f);

        _textInput = std::make_shared<TextInput>(
            _font, sf::Vector2f(0, 0), sf::Vector2f(400, 40));
        _roomHandling = std::make_shared<RoomHandling>(_font);

        _roomContainer.setFillColor(sf::Color(20, 20, 20));
        _roomContainer.setOutlineColor(sf::Color::White);
        _roomContainer.setOutlineThickness(2);

        _outerContainer.setFillColor(sf::Color(15, 15, 15));
        _outerContainer.setOutlineColor(sf::Color::White);
        _outerContainer.setOutlineThickness(3);

        _playerNameText.setFont(_font);
        _playerNameText.setString("Player: " + _playerName);
        _playerNameText.setCharacterSize(20);
        _playerNameText.setFillColor(sf::Color::White);
    }

    void Menu::run(bool &isRunning)
    {
        while (isRunning) {
            handleEvents(isRunning);
            update();
            render();
        }
    }

    void Menu::handleEvents(bool &_in_menu)
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y));

                if (_validateButton.getGlobalBounds().contains(mousePosF)) {
                    if (!_textInput->getText().empty()) {
                        _createdRoom = _textInput->getText();
                        _roomHandling->addRoom(_textInput->getText());
                        _textInput->clear();
                        _client.send_server_create_room(_createdRoom);
                    }
                }

                std::string selectedRoom =
                    _roomHandling->handleClick(mousePosF, _roomContainer);
                if (!selectedRoom.empty()) {
                    _client.send_server_join_room(selectedRoom, _playerName);
                    _in_menu = false;
                }
            }

            if (event.type == sf::Event::MouseWheelScrolled) {
                _roomHandling->handleScroll(event.mouseWheelScroll.delta);
            }

            _textInput->handleEvent(event);
        }
    }

    void Menu::update()
    {
        sf::Vector2u windowSize = _window.getSize();

        _logo.setPosition(
            (windowSize.x - _logo.getGlobalBounds().width) / 2, 20);

        _roomContainer.setSize({windowSize.x * 0.8f, windowSize.y * 0.5f});
        _roomContainer.setPosition(
            (windowSize.x - _roomContainer.getSize().x) / 2,
            _logo.getPosition().y + _logo.getGlobalBounds().height + 20);

        _outerContainer.setSize(
            {_roomContainer.getSize().x, _roomContainer.getSize().y + 100});
        _outerContainer.setPosition(
            _roomContainer.getPosition().x, _roomContainer.getPosition().y);

        _textInput->setPosition({_roomContainer.getPosition().x + 20,
            _roomContainer.getPosition().y + _roomContainer.getSize().y + 20});
        _validateButton.setPosition(_roomContainer.getPosition().x
                + _roomContainer.getSize().x
                - _validateButton.getGlobalBounds().width - 20,
            _roomContainer.getPosition().y + _roomContainer.getSize().y + 10);
        _playerNameText.setPosition(
            windowSize.x - _playerNameText.getLocalBounds().width - 20, 10);
    }

    void Menu::render()
    {
        _window.clear(sf::Color::Black);

        _window.draw(_outerContainer);
        _window.draw(_roomContainer);
        _roomHandling->draw(_window, _roomContainer);
        _textInput->draw(_window);
        _window.draw(_validateButton);
        _window.draw(_logo);
        _window.draw(_playerNameText);

        _window.display();
    }
} // namespace rtype