/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Systems
*/

#include "Client.hpp"

namespace rtype
{
    void Client::set_window_filter(FILTER_MODE filter)
    {
        _filter_system.setFilter(_ecs._components_arrays, filter);
    }

    void Client::change_player_direction(ecs::direction x, ecs::direction y)
    {
        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(x, y, _player_system.getIndexPlayer(_ecs._components_arrays));
        send_server_player_direction(x, y);
        _eventBus.emit(RTYPE_ACTIONS::UPDATE_PLAYER_DIRECTION, std::ref(_x_y));
    }

    void Client::handleMousePress()
    {
        _mouse_pressed = true;
        _mouse_press_time = std::chrono::steady_clock::now();
    }

    void Client::handleMouseRelease()
    {
        if (!_mouse_pressed)
            return;

        _mouse_pressed = false;
        auto isLevelChosen = _ath_system.isLevelClicked(_ecs._components_arrays);
        if (isLevelChosen.first && _levels_wins[isLevelChosen.second]) {
            init_score();
            send_server_start_game(isLevelChosen.second);
        } else if (_ath_system.isLooseOrWinClicked(_ecs._components_arrays)) {
            restart_game();
        } else if (_player_system.getIndexPlayer(_ecs._components_arrays) != -1) {
            auto release_time = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(release_time - _mouse_press_time).count();

            if (duration >= 2000) {
                send_server_new_shoot(true);
            } else {
                send_server_new_shoot(false);
            }
        }
    }

    void Client::handleMouseClick()
    {
        auto isLevelChosen = _ath_system.isLevelClicked(_ecs._components_arrays);
        if (isLevelChosen.first && _levels_wins[isLevelChosen.second]) {
            init_score();
            send_server_start_game(isLevelChosen.second);
        } else if (_ath_system.isLooseOrWinClicked(_ecs._components_arrays)) {
            restart_game();
        } else if (_player_system.getIndexPlayer(_ecs._components_arrays) != -1) {
            send_server_new_shoot();
        }
    }

    void Client::execute_animation() {
        if (!_mouse_pressed)
        {
            size_t index = _animation_system.getChargedAnimationIndex(_ecs._components_arrays);
            if (index != 0)
                _kill_system.killEntity(_ecs, index);
            return;
        }
        std::pair<float, float> player_positions = _position_system.getPlayerPosition(_player_system.getIndexPlayer(_ecs._components_arrays), _ecs._components_arrays);
        player_positions.first += 100;

        if (_animation_system.isAlreadyAnimation(_ecs._components_arrays)) {
            _animation_system.updateChargedAnimation(_ecs._components_arrays, player_positions);
            return;
        }

        auto release_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(release_time - _mouse_press_time).count();

        if (duration > 100) {
            size_t index =  getNextIndex();
            _ecs.addComponents<ecs::Position>(index, ecs::Position(player_positions.first, player_positions.second));
            _ecs.addComponents<Displayable>(index, Displayable(SPRITES::CHARGED_ANIMATION));
            _ecs.addComponents<Animation>(index, Animation());
        }
    }
}