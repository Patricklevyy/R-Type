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
        if (!_font.loadFromFile("assets/fonts/Georgia Regular font.ttf")
            || !_logoTexture.loadFromFile("assets/backgrounds/logo.png")
            || !_createRoomTexture.loadFromFile(
                "assets/backgrounds/create_room_button.png")
            || !_settingsTexture.loadFromFile(
                "assets/settings/settings_button.png")
            || !font_2.loadFromFile("assets/fonts/VeniteAdoremusStraight-Yzo6v.ttf")
            || !_backgroundTexture.loadFromFile("assets/settings/menu_background.jpg")) {
            throw std::runtime_error("Failed to load resources");
        }

        _logo.setTexture(_logoTexture);
        _logo.setScale(0.3f, 0.3f);

        _settings.setTexture(_settingsTexture);

        _validateButton.setTexture(_createRoomTexture);
        _validateButton.setScale(0.3f, 0.3f);

        _textInput = std::make_shared<TextInput>(
            _font, sf::Vector2f(0, 0), sf::Vector2f(400, 40));
        _roomHandling =
            std::make_shared<RoomHandling>(_font, _client._roomsList);
        _background.setTexture(_backgroundTexture);
        // _client.requestRoomList();
        // roomsList = _client._roomsList;
        // for (const auto &room : roomsList) {
        //     _roomHandling->addRoom(room.first, room.second);
        // }

        _roomContainer.setFillColor(sf::Color(20, 20, 20));
        _roomContainer.setOutlineColor(sf::Color::White);
        _roomContainer.setOutlineThickness(2);

        _outerContainer.setFillColor(sf::Color(15, 15, 15));
        _outerContainer.setOutlineColor(sf::Color::White);
        _outerContainer.setOutlineThickness(3);

        _playerText.setFont(font_2);
        _playerText.setString("Player:");
        _playerText.setCharacterSize(20);
        _playerText.setStyle(sf::Text::Underlined);
        _playerText.setFillColor(sf::Color::White);

        _playerNameText.setFont(font_2);
        _playerNameText.setString(_playerName);
        _playerNameText.setCharacterSize(20);
        _playerNameText.setFillColor(sf::Color::Red);
    }

    void Menu::run(bool &inMenu)
    {
        while (inMenu) {
            syncRooms();
            handleEvents(inMenu);
            update();
            render();
        }
    }

    void Menu::joinRoomEvent()
    {
        const std::string roomName = _textInput->getText();

        if (!roomName.empty()) {
            roomsList = _client._roomsList;

            auto it = std::find_if(roomsList.begin(), roomsList.end(),
                [&roomName](const auto &room) {
                    return room.first == roomName;
                });
            int nb_places = 0;
            if (it != roomsList.end()) {
                nb_places = it->second;
            }
            _roomHandling->addRoom(roomName, nb_places);
            _textInput->clear();
            _client.send_server_create_room(roomName);
        }
    }

    void Menu::handleEvents(bool &_in_menu)
    {
        sf::Event event;
        bool inSettings = false;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                _in_menu = false;
                _client._running = false;
                _window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y));

                if (_validateButton.getGlobalBounds().contains(mousePosF)) {
                    joinRoomEvent();
                }

                std::string selectedRoom =
                    _roomHandling->handleClick(mousePosF, _roomContainer);
                if (!selectedRoom.empty()) {
                    _client.send_server_join_room(selectedRoom, _playerName);
                    _in_menu = false;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y));
                if (_settings.getGlobalBounds().contains(mousePosF)) {
                    inSettings = true;
                    auto keyBidingsMap = _client._sfml_handler->getKeyBindings();

                    Settings settings(_window, keyBidingsMap, _client);
                    settings.run(inSettings);
                }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Enter) {
                    joinRoomEvent();
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

        _playerText.setPosition(30, 30);
        _playerNameText.setPosition(_playerText.getPosition().x + _playerText.getGlobalBounds().width + 20, 30);

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
        _settings.setPosition(
            windowSize.x - _settings.getLocalBounds().width - 20, 20);
    }

    void Menu::syncRooms()
    {
        std::lock_guard<std::mutex> lock(_client.roomListMutex);
        for (const auto &room : roomsList) {
            auto it = std::find_if(_roomHandling->_rooms.begin(),
                _roomHandling->_rooms.end(), [&room](const auto &existingRoom) {
                    return existingRoom.first == room.first;
                });

            if (it != _roomHandling->_rooms.end()) {
                if (it->second != room.second) {
                    it->second = room.second;
                }
            } else {
                _roomHandling->addRoom(room.first, room.second);
            }
        }
    }

    void Menu::render()
    {
        auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(
            _client._ecs._components_arrays.at(typeid(Shader)));
        auto leshader = shader[0].value().getShader().get();
        _window.clear(sf::Color::Black);
        _window.draw(_background, leshader);

        _window.draw(_outerContainer);
        _window.draw(_roomContainer);
        _window.draw(_settings, leshader);
        _roomHandling->draw(_window, _roomContainer);
        _textInput->draw(_window);
        _window.draw(_validateButton, leshader);
        _window.draw(_logo, leshader);
        _window.draw(_playerText, leshader);
        _window.draw(_playerNameText, leshader);

        _window.display();
    }
} // namespace rtype