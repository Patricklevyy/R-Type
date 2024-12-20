/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Event_Bus
*/

#include "Room.hpp"

namespace rtype
{
    void Room::init_event_bus()
    {
        // SUBSCRIBE POSITION SYSTEM
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [this](const std::vector<std::any> &args) {
            (void)args;
            _positon_system.updatePositions(_ecs._components_arrays, _timer.getTps(), _window_width, _window_height);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_DIRECTION, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();
                std::tuple<ecs::direction, ecs::direction, size_t> _x_y_index = Utils::extractPlayerPosIndex(message.params, message.id);

                _direction_system.updatePlayerDirection(_ecs._components_arrays, std::get<0>(_x_y_index), std::get<1>(_x_y_index), std::get<2>(_x_y_index));
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::PLAYER_SHOOT, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                createAlliesProjectile(message);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_OFF_SCREEN, [this](const std::vector<std::any> &args) {
            try {
                (void)args;

                std::list<size_t> dead_entites_id = _boundaries_system.checkAndKillEntities(_ecs, _window_width, _window_height);
                if (!dead_entites_id.empty())
                    send_client_dead_entities(dead_entites_id);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::MOVE_MONSTERS, [this](const std::vector<std::any>& args) {
            (void)args;
            _monster_movement_system.moveMonsters(_ecs, _window_width, _window_height, _random_number);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_COLLISIONS, [this](const std::vector<std::any> &args) {
            (void)args;
            _collision_system.detectCollisions(_ecs._components_arrays);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_LIFES, [this](const std::vector<std::any> &args) {
            (void)args;
            std::tuple<std::list<size_t>, unsigned int, bool> dead_entities = _health_system.checkAndKillEntities(_ecs, _nb_client);

            _score_system.addToScore(_ecs._components_arrays, std::get<1>(dead_entities));
            std::list<size_t> dead_entites_id = std::get<0>(dead_entities);
            if (!dead_entites_id.empty())
                send_client_dead_entities(dead_entites_id);
            if (std::get<2>(dead_entities)) {
                _nb_client--;
                dead_entites_id = _kill_system.killMonstersAndProjectiles(_ecs);
                send_client_dead_entities(dead_entites_id);
                send_client_level_status(false);
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::START_LEVEL, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                startLevel(static_cast<LEVELS>(message.id));
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::ENEMY_SHOOT, [this](const std::vector<std::any> &args) {
            (void)args;

            std::list<std::tuple<size_t, std::pair<float, float>, SPRITES>> monsters_pos = _shooting_system.monster_shooting(_ecs._components_arrays, _random_number);
            size_t index;
            while (!monsters_pos.empty()) {
                index = getNextIndex();
                std::tuple<size_t, std::pair<float, float>, SPRITES> monster = monsters_pos.front();
                monsters_pos.pop_front();

                std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> pos_dir_sprite = std::make_tuple(
                    std::get<1>(monster),
                    std::make_pair(3, 0),
                    std::get<2>(monster)
                );
                createEnemiesProjectiles(index, pos_dir_sprite);
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::EXECUTE_LEVEL, [this](const std::vector<std::any> &args) {
            (void)args;

            std::list<SPRITES> monsters = _level_system.executeLevel(_ecs, _random_number);

            SPRITES monster;
            while (!monsters.empty()) {
                monster = monsters.front();
                createMonster(monster);
                monsters.pop_front();
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_LEVEL_FINISHED, [this](const std::vector<std::any> &args) {
            (void)args;

            if (_score_system.isLevelFinished(_ecs._components_arrays)) {
                std::list<size_t> dead_entites_id = _kill_system.killMonstersAndProjectiles(_ecs);
                if (!dead_entites_id.empty())
                    send_client_dead_entities(dead_entites_id);
                send_client_level_status(true);
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PLAYER, [this](const std::vector<std::any> &args) {
            (void)args;

            std::pair<float, float> position = get_player_start_position(getNbClient());

            std::vector<char> send_message;
            ecs::udp::Message mes;
            mes.action = RTYPE_ACTIONS::CREATE_PLAYER;
            mes.params = std::to_string(static_cast<int>(position.first)) + ";" + std::to_string(static_cast<int>(position.second));

            std::cout << "CREATE PLAYER \n\n\n\n : " << mes.params << std::endl;
            mes.id = create_player(position, "new_player");
            _message_compressor.serialize(mes, send_message);
            for (const auto &clientAddr : _clientAddresses) {
                _udp_server->sendMessage(send_message, clientAddr);
            }
            _nb_client++;
            index_ecs++;
        });
    }
}