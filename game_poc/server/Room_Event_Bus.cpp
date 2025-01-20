/*
** EPITECH PROJECT, 2025
** R-TYPE
** File description:
** Room_Event_Bus
*/

#include "Room.hpp"

namespace poc_game
{
    void Room::init_event_bus()
    {
        _eventBus.subscribe(POC_GAME_ACTIONS::UPDATE_POSITIONS, [this](const std::vector<std::any> &args) {
            (void)args;
            _positon_system.updatePositions(_ecs._components_arrays, _timer.getTps(), _window_width);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::PLAY, [this](const std::vector<std::any> &args) {
            (void)args;
            start_game();
            player_jump();
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::JUMP, [this](const std::vector<std::any> &args) {
            (void)args;
            player_jump();
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::EXECUTE_GRAVITY, [this](const std::vector<std::any> &args) {
            (void)args;
            if (isPlaying)
                _gravity_system.executeGravity(_ecs._components_arrays);
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::CHECK_OFF_SCREEN, [this](const std::vector<std::any> &args) {
            (void)args;
            std::pair<std::list<size_t>, bool> dead_entites_id = _boundaries_system.checkAndKillEntities(_ecs, _window_width, _window_height);
            if (dead_entites_id.second) {
                isPlaying = false;
                send_client_loose_game();
                std::list<size_t> deads = _kill_system.killEverything(_ecs);
                if (!deads.empty()) {
                    send_client_dead_entities(deads);
                }
            } else if (!dead_entites_id.first.empty()) {
                for (const auto &entity_id : dead_entites_id.first) {
                    _kill_system.killEntity(_ecs, entity_id);
                }
                send_client_dead_entities(dead_entites_id.first);
            }
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::RESTART, [this](const std::vector<std::any> &args) {
            (void)args;
            restart_game();
        });
        _eventBus.subscribe(POC_GAME_ACTIONS::CHECK_COLLISIONS, [this](const std::vector<std::any> &args) {
            (void)args;
            if (_collision_system.detectCollisions(_ecs._components_arrays)) {
                isPlaying = false;
                send_client_loose_game();
                std::list<size_t> deads = _kill_system.killEverything(_ecs);
                if (!deads.empty()) {
                    send_client_dead_entities(deads);
                }
            }
        });
    }
}