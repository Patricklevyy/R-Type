/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** KeyBindingManager
*/

#include "KeyBinding.hpp"

namespace rtype {
    void KeyBindingManager::bindKey(sf::Keyboard::Key key, const std::string &actionName, Action action) {
        _keyBindings[key] = action;
        _actionToKey[actionName] = key;
    }

    void KeyBindingManager::bindMouseButton(sf::Mouse::Button button, const std::string &actionName, Action action) {
        _mouseBindings[button] = action;
        _actionToMouseButton[actionName] = button;
    }

    void KeyBindingManager::unbindKey(sf::Keyboard::Key key) {
        _keyBindings.erase(key);
    }

    void KeyBindingManager::unbindMouseButton(sf::Mouse::Button button) {
        _mouseBindings.erase(button);
    }

    void KeyBindingManager::handleKeyPress(sf::Keyboard::Key key) {
        if (_keyBindings.find(key) != _keyBindings.end()) {
            _keyBindings[key]();
        }
    }

    void KeyBindingManager::handleMousePress(sf::Mouse::Button button) {
        if (_mouseBindings.find(button) != _mouseBindings.end()) {
            _mouseBindings[button]();
        }
    }

    void KeyBindingManager::rebindKey(const std::string &actionName, sf::Keyboard::Key newKey) {
        auto it = _actionToKey.find(actionName);
        if (it != _actionToKey.end()) {
            sf::Keyboard::Key oldKey = it->second;
            _keyBindings.erase(oldKey);
            _keyBindings[newKey] = _keyBindings[oldKey];
            _actionToKey[actionName] = newKey;
        }
    }

    void KeyBindingManager::rebindMouseButton(const std::string &actionName, sf::Mouse::Button newButton) {
        auto it = _actionToMouseButton.find(actionName);
        if (it != _actionToMouseButton.end()) {
            sf::Mouse::Button oldButton = it->second;
            _mouseBindings.erase(oldButton);
            _mouseBindings[newButton] = _mouseBindings[oldButton];
            _actionToMouseButton[actionName] = newButton;
        }
    }
}
