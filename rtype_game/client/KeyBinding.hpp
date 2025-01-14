/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Keybind
*/

/**
 * @file Keybind.hpp
 * @brief Class representing the keybind for the game.
 * The `Keybind` class handles all the keybind-side logic of the game, such as communication
 * with the server, event handling, entity management, and window rendering.
 */

#ifndef KEYBIND_HPP_
    #define KEYBIND_HPP_

    // // INCLUDES

    // #include "../shared/Includes.hpp"
    // #include "../../ecs/Structures_ecs.hpp"

    // // CLASSES

    // #include "SFMLHandler.hpp"
    // #include "../../ecs/udp/MessageCompressor.hpp"
    // #include "../../ecs/udp/UDP_Keybind.hpp"
    // #include "../../ecs/ECS.hpp"
    // #include "../shared/EventBus.hpp"
    // #include "../shared/Timer.hpp"
    // #include "Command_checker.hpp"
    // #include "../shared/Utils.hpp"
    // #include "../shared/GameplayFactory.hpp"

    // // COMPONENTS

    // #include "components/Window.hpp"
    // #include "components/LevelStatus.hpp"
    // #include "components/Displayable.hpp"
    // #include "components/Sprite.hpp"
    // #include "components/Music.hpp"
    // #include "components/Animation.hpp"
    // #include "../shared/components/Levels.hpp"
    // #include "../shared/components/Health.hpp"
    // #include "components/Text.hpp"

    // // SYSTEMS

    // #include "system/UpdateEntitySystem.hpp"
    // #include "system/RenderWindow.hpp"
    // #include "system/Filter.hpp"
    // #include "system/ATH.hpp"
    // #include "system/PlayerSystem.hpp"
    // #include "system/EventWindow.hpp"
    // #include "system/MusicSystem.hpp"
    // #include "system/ScoreSystem.hpp"
    // #include "system/AnimationSystem.hpp"
    // #include "../shared/system/DirectionSystem.hpp"
    // #include "../shared/system/PositionSystem.hpp"
    // #include "../shared/system/KillSystem.hpp"

    // #include <map>
    // #include <functional>
    // #include <SFML/Window/Keyboard.hpp>

    // namespace rtype
    // {
    //     class SFMLHandler;
    //     class KeyBindingManager {
    //     public:
    //         using Action = std::function<void()>;

    //         void bindKey(sf::Keyboard::Key key, Action action) {
    //             _keyBindings[key] = action;
    //         }

    //         void unbindKey(sf::Keyboard::Key key) {
    //             _keyBindings.erase(key);
    //         }

    //         void handleKeyPress(sf::Keyboard::Key key) {
    //             if (_keyBindings.find(key) != _keyBindings.end()) {
    //                 _keyBindings[key]();
    //             }
    //         }

    //     private:
    //         std::map<sf::Keyboard::Key, Action> _keyBindings;
    //     };

    // }
#ifndef KEYBINDINGMANAGER_HPP_
#define KEYBINDINGMANAGER_HPP_

#include <map>
#include <functional>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <string>

namespace rtype
{
    class SFMLHandler;
    class KeyBindingManager {
        public:
            using Action = std::function<void()>;

            KeyBindingManager() = default;
            ~KeyBindingManager() = default;

            // Bind a key to an action
            void bindKey(sf::Keyboard::Key key, const std::string &actionName, Action action);

            // Bind a mouse button to an action
            void bindMouseButton(sf::Mouse::Button button, const std::string &actionName, Action action);

            // Remove a key binding
            void unbindKey(sf::Keyboard::Key key);

            // Remove a mouse button binding
            void unbindMouseButton(sf::Mouse::Button button);

            // Handle a key press event
            void handleKeyPress(sf::Keyboard::Key key);

            // Handle a mouse button press event
            void handleMousePress(sf::Mouse::Button button);

            // Change the key bound to an action
            void rebindKey(const std::string &actionName, sf::Keyboard::Key newKey);

            // Change the mouse button bound to an action
            void rebindMouseButton(const std::string &actionName, sf::Mouse::Button newButton);

        private:
            std::map<sf::Keyboard::Key, Action> _keyBindings;
            std::map<sf::Mouse::Button, Action> _mouseBindings;
            std::map<std::string, sf::Keyboard::Key> _actionToKey;
            std::map<std::string, sf::Mouse::Button> _actionToMouseButton;
    };
}

#endif /* KEYBINDINGMANAGER_HPP_ */

#endif /* !KEYBIND_HPP_ */
