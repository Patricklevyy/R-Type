/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Event_Bus
*/

#include "Room.hpp"

namespace rtype
{
    void Room::spawnWeaponDrop(ecs::ECS &ecs, const std::pair<float, float> &position, size_t index)
    {
        // Room room(0, "room1");
        std::cout << "OK CA RENTRE PELOOOOOO |||||||||||||||||||||||||||" << std::endl;
        // size_t index = room.getNextIndex();
        // size_t index = room.getNextIndex();
        // SpriteId spriteId(SPRITES::WEAPON_DROP);
        // // Displayable displayable(SPRITES::WEAPON_DROP);
        // ecs::Position positions(position.first, position.second);

        // std::cout << "pos x = " << positions._pos_x << " , pos y = " << positions._pos_y << " , index = " << index << std::endl;
        // ecs.addComponents<SpriteId>(index, spriteId);
        // std::cout << "c'est venu jusque la pelo donc bon" << std::endl;
        // ecs.addComponents<ecs::Position>(index, positions);
        // ecs.addComponents<Hitbox>(index, Hitbox(HitboxFactory::createHitbox(WEAPON_DROP)));
        // ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(MonsterFactory::getMonsterVelocity(WEAPON_DROP)));
        // ecs.addComponents<Monster>(index, Monster(WEAPON_DROP));
        // // ecs.addComponents<Displayable>(index, displayable);
        // // send_client_new_monster(index, positions._pos_x, positions._pos_y, WEAPON_DROP);
        // // room->send_client_new_monster(index, positions._pos_x, positions._pos_y, WEAPON_DROP);
        // // _ecs.addComponents<ecs::Position>(index, positions);
        // std::cout << "Weapon drop entity created at X: " << position.first << ", Y: " << position.second << std::endl;
    }

    void Room::init_event_bus()
    {
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITIONS, [this](const std::vector<std::any> &args) {
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
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PROJECTILE, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                createProjectiles(message);
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
        // _eventBus.subscribe(RTYPE_ACTIONS::CHECK_LIFES, [this](const std::vector<std::any> &args) {
        //     (void)args;

        //     size_t index = getNextIndex();
        //     std::cout << "temp value with back = " << index << std::endl;
        //     std::tuple<std::list<size_t>, unsigned int, bool, std::list<std::pair<float, float>>> dead_entities = _health_system.checkLife(_ecs, _nb_client);
        //     // std::tuple<std::list<size_t>, unsigned int, bool> dead_entities = _health_system.checkLife(_ecs, _nb_client);

        //     std::list<std::pair<float, float>> dead_entities_positions = std::get<3>(dead_entities);
        //     auto position_it = dead_entities_positions.begin();

        //     if (std::get<1>(dead_entities) != 0) {
        //         _level_system.addToScore(_ecs._components_arrays, std::get<1>(dead_entities));
        //         sendScore(_level_system.getScore(_ecs._components_arrays));
        //     }
        //     std::list<size_t> dead_entites_id = std::get<0>(dead_entities);
        //     auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(_ecs._components_arrays[typeid(Monster)]);
        //     for (const auto &entity_id : dead_entites_id) {
        //         // std::cout << "OKKKKKKKKKKKKKKK||||||||||||" << entity_id << std::endl;
        //         // if (entity_id < monsters.size() && monsters[entity_id].has_value()) {
        //         //     int lucky = rand() % 100;
        //         //     // if (lucky <= 5) {
        //         //     if (lucky <= 100) {
        //         //         std::cout << "Ah ouais, tu es un chanceux toi peloooooo" << std::endl; // a enlever
        //         //         // std::cout << "Position du monstre tué: X = " << position._pos_x << ", Y = " << position._pos_y << std::endl;
        //         //         const auto &position = *position_it;
        //         //         std::cout << "Position du monstre tué : X = " << position.first << ", Y = " << position.second << std::endl;
        //         //         // spawnWeaponDrop(_ecs, position, index);
        //         //         ++position_it;
        //         //         std::cout << "OK, c'est revenu dans la fonction de base pelloooooooo" << std::endl;
        //         //     }
        //         // }
        //         _kill_system.killEntity(_ecs, entity_id);
        //     }
        //     if (!dead_entites_id.empty())
        //         send_client_dead_entities(dead_entites_id);
        //     if (std::get<2>(dead_entities)) {
        //         if (_nb_client > 0)
        //             _nb_client--;
        //         dead_entites_id = _kill_system.killMonstersAndProjectiles(_ecs);
        //         send_client_dead_entities(dead_entites_id);
        //         send_client_level_status(false, LEVELS::UN);
        //     }
        // });
        // _eventBus.subscribe(RTYPE_ACTIONS::CHECK_LIFES, [this](const std::vector<std::any> &args) {
        //     (void)args;

        //     size_t index = getNextIndex();
        //     std::tuple<std::list<size_t>, unsigned int, bool, std::list<std::pair<float, float>>> dead_entities = _health_system.checkLife(_ecs, _nb_client);
        //     // std::tuple<std::list<size_t>, unsigned int, bool> dead_entities = _health_system.checkLife(_ecs, _nb_client);

        //     if (std::get<1>(dead_entities) != 0) {
        //         _level_system.addToScore(_ecs._components_arrays, std::get<1>(dead_entities));
        //         sendScore(_level_system.getScore(_ecs._components_arrays));
        //     }
        //     std::list<size_t> dead_entites_id = std::get<0>(dead_entities);
        //     for (const auto &entity_id : dead_entites_id) {
        //         _kill_system.killEntity(_ecs, entity_id);
        //     }
        //     if (!dead_entites_id.empty())
        //         send_client_dead_entities(dead_entites_id);
        //     if (std::get<2>(dead_entities)) {
        //         if (_nb_client > 0)
        //             _nb_client--;
        //         dead_entites_id = _kill_system.killMonstersAndProjectiles(_ecs);
        //         send_client_dead_entities(dead_entites_id);
        //         send_client_level_status(false, LEVELS::UN);
        //     }
        // });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_LIFES, [this](const std::vector<std::any> &args) {
            (void)args;

            // size_t index = getNextIndex();
            std::tuple<std::list<size_t>, unsigned int, bool, std::list<std::pair<float, float>>> dead_entities = _health_system.checkLife(_ecs, _nb_client);
            // std::tuple<std::list<size_t>, unsigned int, bool> dead_entities = _health_system.checkLife(_ecs, _nb_client);

            if (std::get<1>(dead_entities) != 0) {
                _level_system.addToScore(_ecs._components_arrays, std::get<1>(dead_entities));
                sendScore(_level_system.getScore(_ecs._components_arrays));
            }
            std::list<size_t> dead_entites_id = std::get<0>(dead_entities);
            std::list<std::pair<float, float>> dead_entities_positions = std::get<3>(dead_entities);
            auto position_it = dead_entities_positions.begin();
            auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(_ecs._components_arrays[typeid(Monster)]);
            for (const auto &entity_id : dead_entites_id) {
                if (entity_id < monsters.size() && monsters[entity_id].has_value()) {
                    int lucky = rand() % 100;
                    if (lucky <= 100) {
                        std::cout << "ouais raconte pas ta vie frérot" << std::endl;
                        const auto &position = *position_it;
                        ++position_it;
                        // spawnWeaponDrop(_ecs, position, index);
                    }
                 }
                _kill_system.killEntity(_ecs, entity_id);
            }
            if (!dead_entites_id.empty())
                send_client_dead_entities(dead_entites_id);
            if (std::get<2>(dead_entities)) {
                if (_nb_client > 0)
                    _nb_client--;
                dead_entites_id = _kill_system.killMonstersAndProjectiles(_ecs);
                send_client_dead_entities(dead_entites_id);
                send_client_level_status(false, LEVELS::UN);
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
                createEntityProjectiles(index, pos_dir_sprite);
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

            std::pair<LEVELS, bool> level = _level_system.isLevelFinished(_ecs._components_arrays);
            if (level.second) {
                std::list<size_t> dead_entites_id = _kill_system.killMonstersAndProjectiles(_ecs);
                if (!dead_entites_id.empty())
                    send_client_dead_entities(dead_entites_id);
                send_client_level_status(level.second, level.first);
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PLAYER, [this](const std::vector<std::any> &args) {
            (void)args;

            std::pair<float, float> position = get_player_start_position(getNbClient());

            std::vector<char> send_message;
            ecs::udp::Message mes;
            mes.action = RTYPE_ACTIONS::CREATE_PLAYER;
            mes.params = std::to_string(static_cast<int>(position.first)) + ";" + std::to_string(static_cast<int>(position.second));

            mes.id = create_player(position, "new_player");
            _message_compressor.serialize(mes, send_message);
            for (const auto &clientAddr : _clientAddresses) {
                _udp_server->sendMessage(send_message, clientAddr);
            }
            _nb_client++;
        });
    }
}