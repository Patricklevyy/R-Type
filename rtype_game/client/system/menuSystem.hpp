#ifndef MENUSYSTEM_HPP_
#define MENUSYSTEM_HPP_

#include "../../../ecs/Includes_ecs.hpp"
#include "../../../ecs/SparseArray.hpp"
#include "../../../ecs/components/Direction.hpp"
#include "../../../rtype_game/client/components/Window.hpp"
#include "../../shared/EventBus.hpp"

namespace rtype {

class MenuSystem {
public:
    MenuSystem(int width = 800, int height = 600, const std::string &title = "R-Type Menu");

    MenuSystem(EventBus &eventBus) : _eventBus(eventBus) {}

    void start(std::unordered_map<std::type_index, std::any> &components) {
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

private:
    EventBus &_eventBus;
    std::shared_ptr<sf::RenderWindow> _window;
    sf::Font _font;
    sf::Texture _backgroundTexture;
    sf::Sprite _backgroundSprite;

    bool _running = false;

    struct MenuItem {
        sf::Text label;
        std::function<void()> action;
    };

    std::vector<MenuItem> _menuItems;
    std::size_t _currentSelection = 0;

    void initializeMenu() {
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

    void positionMenu() {
        float startY = _window->getSize().y / 2.f - (_menuItems.size() * 50 / 2);
        for (std::size_t i = 0; i < _menuItems.size(); ++i) {
            _menuItems[i].label.setPosition(_window->getSize().x / 2.f, startY + i * 50);
            centerText(_menuItems[i].label);
        }
    }

    void centerText(sf::Text &text) {
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    }

    void handleEvents() {
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

    void render() {
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
};

} // namespace rtype

#endif /* !MENUSYSTEM_HPP_ */
