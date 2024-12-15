#include "menuSystem.hpp"

namespace rtype {

MenuSystem::MenuSystem(int width, int height, const std::string &title)
    : _window(std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title)), _running(false) {}

void MenuSystem::start(std::unordered_map<std::type_index, std::any> &components) {
    auto &windows = std::any_cast<ecs::SparseArray<Window> &>(components[typeid(Window)]);

    for (std::size_t i = 0; i < windows.size(); ++i) {
        if (windows[i].has_value()) {
            _window = windows[i].value().getRenderWindow();
        }
    }

    if (!_font.loadFromFile("rtype_game/client/menu/assets/arial.ttf")) {
        throw std::runtime_error("Failed to load font");
    }

    if (!_backgroundTexture.loadFromFile("rtype_game/client/menu/assets/espace.jpeg")) {
        throw std::runtime_error("Failed to load background texture");
    }

    _backgroundSprite.setTexture(_backgroundTexture);

    initializeMenu();
    _running = true;

    while (_running && _window->isOpen()) {
        handleEvents();
        render();
    }
}

void MenuSystem::initializeMenu() {
    _menuItems = {
        {"Start Game", [this]() { _running = false; }},
        {"Create Room", [this]() { std::cout << "Create Room selected\n"; }},
        {"Join Room", [this]() { std::cout << "Join Room selected\n"; }},
        {"Exit", [this]() { _window->close(); }}
    };

    for (auto &item : _menuItems) {
        item.label.setFont(_font);
        item.label.setCharacterSize(30);
        item.label.setFillColor(sf::Color::White);
    }

    positionMenu();
}

void MenuSystem::positionMenu() {
    float startY = _window->getSize().y / 2.f - (_menuItems.size() * 50 / 2);
    for (std::size_t i = 0; i < _menuItems.size(); ++i) {
        _menuItems[i].label.setPosition(_window->getSize().x / 2.f, startY + i * 50);
        centerText(_menuItems[i].label);
    }
}

void MenuSystem::centerText(sf::Text &text) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void MenuSystem::handleEvents() {
    sf::Event event;
    while (_window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            _window->close();
        }

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up) {
                _currentSelection = (_currentSelection - 1 + _menuItems.size()) % _menuItems.size();
            } else if (event.key.code == sf::Keyboard::Down) {
                _currentSelection = (_currentSelection + 1) % _menuItems.size();
            } else if (event.key.code == sf::Keyboard::Enter) {
                _menuItems[_currentSelection].action();
            }
        }
    }
}

void MenuSystem::render() {
    _window->clear();
    _window->draw(_backgroundSprite);

    for (std::size_t i = 0; i < _menuItems.size(); ++i) {
        if (i == _currentSelection) {
            _menuItems[i].label.setFillColor(sf::Color::Red);
        } else {
            _menuItems[i].label.setFillColor(sf::Color::White);
        }
        _window->draw(_menuItems[i].label);
    }

    _window->display();
}

} // namespace rtype
