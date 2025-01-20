/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Systems
*/

#include "Client.hpp"

namespace poc_game
{
    void Client::handleMouseClick()
    {
        if (_ath_system.isPlayButtonClicked(_ecs._components_arrays)
            && !first) {
            send_server_start_game();
            first = true;
        } else if (_ath_system.isPlayButtonClicked(_ecs._components_arrays)
            && first) {
            _kill_system.killTempDisplay(_ecs);
            send_server_restart_game();
        } else if (!is_playing) {
            send_server_playing();
            is_playing = true;
        } else if (is_playing) {
            send_server_jump();
        }
    }

    void Client::restart_game(ecs::udp::Message &message)
    {
        size_t pos = message.params.find(':');

        std::string player_room = message.params.substr(0, pos);
        std::string entities = message.params.substr(pos + 1);

        std::tuple<float, float, int> pos_port =
            Utils::parsePositionAndRoomPort(player_room);

        _ath_system.removePlayButtons(_ecs);
        init_player(message.id, std::get<0>(pos_port), std::get<1>(pos_port));
    }
} // namespace poc_game