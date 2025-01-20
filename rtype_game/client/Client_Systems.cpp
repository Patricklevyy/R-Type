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
        size_t player_index = _player_system.getIndexPlayer(_ecs._components_arrays);
        if (player_index == 0)
            return;
        std::tuple<ecs::direction, ecs::direction, size_t> _x_y(x, y, player_index);
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
            send_server_start_game(isLevelChosen.second);
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

    void Client::execute_animation() {
        if (!_mouse_pressed)
        {
            size_t index = _animation_system.getChargedAnimationIndex(_ecs._components_arrays);
            if (index != 0)
                _kill_system.killEntity(_ecs, index);
            return;
        }
        int index_player = _player_system.getIndexPlayer(_ecs._components_arrays);
        if (index_player == -1)
            return;
        std::pair<float, float> player_positions = _position_system.getPlayerPosition(index_player, _ecs._components_arrays);
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

    std::vector<std::pair<std::string, int>> Client::parseRoomList(const std::string &roomList)
    {
        std::vector<std::pair<std::string, int>> parsedRooms;
        std::stringstream ss(roomList);
        std::string roomEntry;

        while (std::getline(ss, roomEntry, ':')) {
            size_t prefixPos = roomEntry.find("rooms=");
            if (prefixPos != std::string::npos) {
                roomEntry = roomEntry.substr(prefixPos + 6);

                size_t delimiterPos = roomEntry.find(',');
                if (delimiterPos != std::string::npos) {
                    std::string roomName = roomEntry.substr(0, delimiterPos);
                    int nbClients = std::stoi(roomEntry.substr(delimiterPos + 1));
                    parsedRooms.emplace_back(roomName, nbClients);
                }
            }
        }
        return parsedRooms;
    }

    void Client::updatePlayerLife(std::string lifes_string)
    {
        std::list<std::pair<size_t, int>> lifes = Utils::parse_update_life(lifes_string);

        std::pair<bool, int> player;
        for (auto life : lifes) {
            player = _player_system.updatePlayerLife(_ecs._components_arrays, ecs_server_to_client[life.first], life.second);

            if (player.first) {
                _player_system.updateLifeDisplay(_ecs._components_arrays, ecs_server_to_client[life.first]);
                return;
            }
        }
    }

    void Client::levelStatusTime()
    {
        static auto lastTime = std::chrono::steady_clock::now();

        auto currentTime = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(currentTime - lastTime).count();

        if (elapsed > 5) {
            _inLevelStatus = false;
            restart_game();
        }
    }
}