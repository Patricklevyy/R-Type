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

    void Client::handleMouseClick()
    {
        auto isLevelChosen = _ath_system.isLevelClicked(_ecs._components_arrays);

        if (isLevelChosen.first && _levels_wins[isLevelChosen.second]) {
            send_server_start_game(isLevelChosen.second);
        } else if (_ath_system.isLooseOrWinClicked(_ecs._components_arrays)) {
            restart_game();
        } else if (_player_system.getIndexPlayer(_ecs._components_arrays) != -1) {
            send_server_new_shoot();
        }

        // Vérifie si le bouton "Exit" est cliqué
        auto mousePos = _ath_system.getMousePosition(_ecs._components_arrays);
        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(_ecs._components_arrays.at(typeid(ecs::Position)));
        auto &displayables = std::any_cast<ecs::SparseArray<Displayable> &>(_ecs._components_arrays.at(typeid(Displayable)));

        for (std::size_t i = 0; i < positions.size(); ++i) {
            if (displayables[i].has_value() && positions[i].has_value() && displayables[i].value().getSpriteSize().x != 0) {
                if (mousePos.x >= positions[i].value()._pos_x &&
                    mousePos.x <= positions[i].value()._pos_x + displayables[i].value().getSpriteSize().x &&
                    mousePos.y >= positions[i].value()._pos_y &&
                    mousePos.y <= positions[i].value()._pos_y + displayables[i].value().getSpriteSize().y &&
                    displayables[i].value().getSpriteId() == SPRITES::EXIT_BUTTON) { // Vérifie l'ID du sprite
                    _running = false; // Arrête le jeu
                    return;
                }
            }
        }
    }
}