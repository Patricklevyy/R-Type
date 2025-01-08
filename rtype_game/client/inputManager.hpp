#ifndef INPUTMANAGER_HPP_
#define INPUTMANAGER_HPP_

#include <SFML/Window.hpp>
#include <unordered_map>
#include <string>

namespace rtype {

    class InputManager {
    public:
        InputManager() {
            // Définir les touches par défaut
            _keyBindings["move_up"] = sf::Keyboard::Z; // Par défaut : 'Z'
        }

        void bindKey(const std::string &action, sf::Keyboard::Key key) {
            _keyBindings[action] = key;
        }

        sf::Keyboard::Key getKey(const std::string &action) const {
            if (_keyBindings.find(action) != _keyBindings.end()) {
                return _keyBindings.at(action);
            }
            return sf::Keyboard::Unknown;
        }

        bool isKeyPressed(const std::string &action) const {
            auto key = getKey(action);
            if (key != sf::Keyboard::Unknown) {
                return sf::Keyboard::isKeyPressed(key);
            }
            return false;
        }

    private:
        std::unordered_map<std::string, sf::Keyboard::Key> _keyBindings;
    };

}

#endif // INPUTMANAGER_HPP_
