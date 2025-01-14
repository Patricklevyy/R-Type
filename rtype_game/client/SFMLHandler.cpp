/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SFMLHandler
*/

#include "SFMLHandler.hpp"

namespace rtype
{
    // SFMLHandler::SFMLHandler(Client &client) : _client(client)
    // {
    // }
    SFMLHandler::SFMLHandler(Client &client)
        : _client(client)
    {
        // Default key bindings
        _keyBindingManager.bindKey(sf::Keyboard::Escape, "exit", [&]() {
            _client._running = false;
        });
    
        // Movement bindings
        _keyBindingManager.bindKey(sf::Keyboard::W, "move_up", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::UP);
        });
    
        _keyBindingManager.bindKey(sf::Keyboard::S, "move_down", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::DOWN);
        });
    
        _keyBindingManager.bindKey(sf::Keyboard::D, "move_right", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::RIGHT, ecs::direction::NO_CHANGE);
        });
    
        _keyBindingManager.bindKey(sf::Keyboard::A, "move_left", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::LEFT, ecs::direction::NO_CHANGE);
        });
    
        // Stop movement
        _keyBindingManager.bindKey(sf::Keyboard::Up, "move_up_stop", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
        });
    
        _keyBindingManager.bindKey(sf::Keyboard::Down, "move_down_stop", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
        });
    
        _keyBindingManager.bindKey(sf::Keyboard::Right, "move_right_stop", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
        });
    
        _keyBindingManager.bindKey(sf::Keyboard::Left, "move_left_stop", [&]() {
            if (!_client._in_menu)
                _client.change_player_direction(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
        });
    
        // Shooting action
        _keyBindingManager.bindKey(sf::Keyboard::Space, "player_shoot", [&]() {
            if (!_client._in_menu)
                _client.handle_action(RTYPE_ACTIONS::PLAYER_SHOOT);
        });
    
        // Join room
        _keyBindingManager.bindKey(sf::Keyboard::J, "join_room", [&]() {
            _client.handle_action(RTYPE_ACTIONS::JOIN_ROOM);
        });
    
        // Leave room
        _keyBindingManager.bindKey(sf::Keyboard::L, "leave_room", [&]() {
            _client.handle_action(RTYPE_ACTIONS::LEAVE_ROOM);
        });
    
        // Start level
        _keyBindingManager.bindKey(sf::Keyboard::Enter, "start_level", [&]() {
            _client.handle_action(RTYPE_ACTIONS::START_LEVEL);
        });
    
        // Render window
        _keyBindingManager.bindKey(sf::Keyboard::R, "render_window", [&]() {
            _client.handle_action(RTYPE_ACTIONS::RENDER_WINDOW);
        });
    
        // Fail level
        _keyBindingManager.bindKey(sf::Keyboard::F, "fail_level", [&]() {
            _client.handle_action(RTYPE_ACTIONS::FAIL_LEVEL);
        });
    
        // Win level
        _keyBindingManager.bindKey(sf::Keyboard::P, "win_level", [&]() {
            _client.handle_action(RTYPE_ACTIONS::WIN_LEVEL);
        });
    
        // Add other default bindings here...
    }

    SFMLHandler::~SFMLHandler()
    {
    }

    void SFMLHandler::handleEvents(std::queue<sf::Event> &events)
    {
        while (!events.empty())
        {
            sf::Event event = events.front();
            events.pop();

            switch (event.type)
            {
            case sf::Event::Closed:
                _client._running = false;
                return;

            case sf::Event::KeyPressed:
                processKeyPressed(event);
                break;

            case sf::Event::KeyReleased:
                processKeyReleased(event);
                break;

            case sf::Event::MouseButtonPressed:
                processMouseButtonPressed(event);
                break;

            case sf::Event::MouseButtonReleased:
                processMouseButtonReleased(event);
                break;

            default:
                break;
            }
        }
    }

    // void SFMLHandler::processKeyPressed(const sf::Event &event)
    // {
    //     if (event.key.code == sf::Keyboard::Escape) {
    //         // Close the client
    //         _client._running = false;
    //         return;
    //     }

    //     if (event.key.code == sf::Keyboard::D && !_client._in_menu) {
    //         _client.change_player_direction(
    //             ecs::direction::RIGHT, ecs::direction::NO_CHANGE);
    //     }
    //     if (event.key.code == sf::Keyboard::Q && !_client._in_menu) {
    //         _client.change_player_direction(
    //             ecs::direction::LEFT, ecs::direction::NO_CHANGE);
    //     }
    //     if (event.key.code == sf::Keyboard::Z && !_client._in_menu) {
    //         _client.change_player_direction(
    //             ecs::direction::NO_CHANGE, ecs::direction::UP);
    //     }
    //     if (event.key.code == sf::Keyboard::S && !_client._in_menu) {
    //         _client.change_player_direction(
    //             ecs::direction::NO_CHANGE, ecs::direction::DOWN);
    //     }
    //     // if (event.key.code == sf::Keyboard::A)
    //     // {
    //     //     _client.send_server_create_room("uneroom");
    //     // }
    //     // if (event.key.code == sf::Keyboard::B)
    //     // {
    //     //     _client.send_server_join_room("uneroom", "Patoche");
    //     // }
    //     if (event.key.code == sf::Keyboard::Num1) {
    //         _client.set_window_filter(FILTER_MODE::Neutral);
    //     }
    //     if (event.key.code == sf::Keyboard::Num2) {
    //         _client.set_window_filter(FILTER_MODE::Inverted);
    //     }
    //     if (event.key.code == sf::Keyboard::Num3) {
    //         _client.set_window_filter(FILTER_MODE::Protanopia);
    //     }
    //     if (event.key.code == sf::Keyboard::Num4) {
    //         _client.set_window_filter(FILTER_MODE::Deuteranopia);
    //     }
    //     if (event.key.code == sf::Keyboard::Num5) {
    //         _client.set_window_filter(FILTER_MODE::Tritanopia);
    //     }
    // }

    void SFMLHandler::processKeyReleased(const sf::Event &event)
    {
        if (!_client._in_menu)
        {
            if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Q)
            {
                _client.change_player_direction(ecs::direction::NO_DIRECTION, ecs::direction::NO_CHANGE);
            }
            if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::S)
            {
                _client.change_player_direction(ecs::direction::NO_CHANGE, ecs::direction::NO_DIRECTION);
            }
        }
    }

    void SFMLHandler::processKeyPressed(const sf::Event &event) {
        _keyBindingManager.handleKeyPress(event.key.code);
    }

    // Refactor processMouseButtonPressed to use the KeyBindingManager
    void SFMLHandler::processMouseButtonPressed(const sf::Event &event) {
        _keyBindingManager.handleMousePress(event.mouseButton.button);
    }

    // void SFMLHandler::processMouseButtonPressed(const sf::Event &event)
    // {
    //     if (event.mouseButton.button == sf::Mouse::Left) {
    //         _client.handleMousePress(); // Commence un tir
    //     }
    // }

    void SFMLHandler::processMouseButtonReleased(const sf::Event &event)
    {
        if (event.mouseButton.button == sf::Mouse::Left) {
            _client.handleMouseRelease(); // Termine le tir
        }
    }
}