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
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITIONS,
            [this](const std::vector<std::any> &args) {
                (void) args;
                _positon_system.updatePositions(_ecs._components_arrays,
                    _timer.getTps(), _window_width, _window_height);
            });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_DIRECTION,
            [this](const std::vector<std::any> &args) {
                try {
                    ecs::udp::Message message = std::any_cast<
                        std::reference_wrapper<ecs::udp::Message>>(args[0])
                                                    .get();
                    std::tuple<ecs::direction, ecs::direction, size_t>
                        _x_y_index = Utils::extractPlayerPosIndex(
                            message.params, message.id);

                    _direction_system.updatePlayerDirection(
                        _ecs._components_arrays, std::get<0>(_x_y_index),
                        std::get<1>(_x_y_index), std::get<2>(_x_y_index));
                } catch (const std::bad_any_cast &e) {
                    std::cerr << "Error during event handling: dans" << e.what()
                              << std::endl;
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PROJECTILE,
            [this](const std::vector<std::any> &args) {
                try {
                    ecs::udp::Message message = std::any_cast<
                        std::reference_wrapper<ecs::udp::Message>>(args[0])
                                                    .get();

                    createProjectiles(message);
                } catch (const std::bad_any_cast &e) {
                    std::cerr << "Error during event handling: dans" << e.what()
                              << std::endl;
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_OFF_SCREEN,
            [this](const std::vector<std::any> &args) {
                try {
                    (void) args;

                    std::list<size_t> dead_entites_id =
                        _boundaries_system.checkAndKillEntities(
                            _ecs, _window_width, _window_height);
                    if (!dead_entites_id.empty())
                        send_client_dead_entities(dead_entites_id);
                } catch (const std::bad_any_cast &e) {
                    std::cerr << "Error during event handling: dans" << e.what()
                              << std::endl;
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::MOVE_MONSTERS,
            [this](const std::vector<std::any> &args) {
                (void) args;
                _monster_movement_system.moveMonsters(
                    _ecs, _window_width, _window_height, _random_number);
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_COLLISIONS,
            [this](const std::vector<std::any> &args) {
                (void) args;
                _collision_system.detectCollisions(_ecs._components_arrays);
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_LIFES,
            [this](const std::vector<std::any> &args) {
                (void) args;

                std::tuple<std::list<size_t>, unsigned int, bool,
                    std::list<std::pair<float, float>>>
                    dead_entities = _health_system.checkLife(_ecs);

                if (std::get<1>(dead_entities) != 0) {
                    _level_system.addToScore(
                        _ecs._components_arrays, std::get<1>(dead_entities));
                    sendScore(_level_system.getScore(_ecs._components_arrays));
                }
                std::list<size_t> dead_entites_id = std::get<0>(dead_entities);
                std::list<std::pair<float, float>> dead_entities_positions =
                    std::get<3>(dead_entities);
                auto &monsters = std::any_cast<ecs::SparseArray<Monster> &>(
                    _ecs._components_arrays[typeid(Monster)]);

                auto id_it = dead_entites_id.begin();
                auto pos_it = dead_entities_positions.begin();

                for (; id_it != dead_entites_id.end()
                     && pos_it != dead_entities_positions.end();
                     ++id_it, ++pos_it) {
                    size_t entity_id = *id_it;
                    std::pair<float, float> position = *pos_it;

                    if (entity_id < monsters.size()
                        && monsters[entity_id].has_value()) {
                        spawnBonus(position);
                    }
                    _kill_system.killEntity(_ecs, entity_id);
                }
                if (!dead_entites_id.empty())
                    send_client_dead_entities(dead_entites_id);
                if (std::get<2>(dead_entities)) {
                    _eventBus.emit(RTYPE_ACTIONS::UPDATE_LIFE);
                    dead_entites_id = _kill_system.killAllExceptPlayer(_ecs);
                    send_client_dead_entities(dead_entites_id);
                    playingInLevel = false;
                    send_client_level_status(false, LEVELS::UN);
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::START_LEVEL,
            [this](const std::vector<std::any> &args) {
                try {
                    ecs::udp::Message message = std::any_cast<
                        std::reference_wrapper<ecs::udp::Message>>(args[0])
                                                    .get();

                    startLevel(static_cast<LEVELS>(message.id));
                } catch (const std::bad_any_cast &e) {
                    std::cerr << "Error during event handling: dans" << e.what()
                              << std::endl;
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::ENEMY_SHOOT,
            [this](const std::vector<std::any> &args) {
                (void) args;

                std::list<std::tuple<size_t,
                    std::pair<std::pair<float, float>, std::pair<float, float>>,
                    SPRITES>>
                    monsters_pos = _shooting_system.monster_shooting(
                        _ecs._components_arrays, _random_number, _window_width,
                        _window_height);
                size_t index;
                while (!monsters_pos.empty()) {
                    index = getNextIndex();
                    std::tuple<size_t,
                        std::pair<std::pair<float, float>,
                            std::pair<float, float>>,
                        SPRITES>
                        monster = monsters_pos.front();
                    monsters_pos.pop_front();

                    std::tuple<std::pair<float, float>, std::pair<int, int>,
                        SPRITES>
                        pos_dir_sprite = std::make_tuple(
                            std::get<1>(monster).first,
                            std::get<1>(monster).second, std::get<2>(monster));
                    createEntityProjectiles(index, pos_dir_sprite);
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::EXECUTE_LEVEL,
            [this](const std::vector<std::any> &args) {
                (void) args;

                std::list<SPRITES> monsters = _level_system.executeLevel(
                    _ecs, _random_number, _gameplay_factory);

                SPRITES monster;
                while (!monsters.empty()) {
                    monster = monsters.front();
                    createMonster(monster);
                    monsters.pop_front();
                }
                monsters = _level_system.spwanBoss(
                    _ecs, _random_number, _gameplay_factory);

                while (!monsters.empty()) {
                    monster = monsters.front();
                    createBoss(monster);
                    monsters.pop_front();
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_LEVEL_FINISHED,
            [this](const std::vector<std::any> &args) {
                (void) args;

                std::pair<LEVELS, bool> level =
                    _level_system.isLevelFinished(_ecs._components_arrays);
                if (level.second) {
                    std::list<size_t> dead_entites_id =
                        _kill_system.killAllExceptPlayer(_ecs);
                    if (!dead_entites_id.empty())
                        send_client_dead_entities(dead_entites_id);
                    playingInLevel = false;
                    if (_gameplay_factory->getDifficulty()
                        != DIFFICULTY::IMPOSSIBLE)
                        _health_system.resetLifeForPlayers(
                            _ecs._components_arrays);
                    send_client_level_status(level.second, level.first);
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_PLAYER,
            [this](const std::vector<std::any> &args) {
                (void) args;

                std::pair<float, float> position =
                    get_player_start_position(getNbClient());

                std::vector<char> send_message;
                ecs::udp::Message mes;
                mes.action = RTYPE_ACTIONS::CREATE_PLAYER;
                mes.params = std::to_string(static_cast<int>(position.first))
                    + ";" + std::to_string(static_cast<int>(position.second))
                    + ";"
                    + std::to_string(_gameplay_factory->getPlayerHealth());

                mes.id = create_player(position, "new_player");
                _message_compressor.serialize(mes, send_message);
                for (const auto &clientAddr : _clientAddresses) {
                    _udp_server->sendMessage(send_message, clientAddr);
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::SPAWN_ASTEROIDE,
            [this](const std::vector<std::any> &args) {
                (void) args;

                std::list<std::tuple<size_t,
                    std::pair<std::pair<float, float>, std::pair<float, float>>,
                    SPRITES>>
                    asteroides = _asteroide_system.spwan_asteroide(
                        _random_number, _gameplay_factory, _window_height,
                        _window_width, playingInLevel);

                if (asteroides.empty())
                    return;
                size_t index;
                for (const auto &asteroide : asteroides) {
                    index = getNextIndex();
                    std::tuple<std::pair<float, float>, std::pair<int, int>,
                        SPRITES>
                        pos_dir_sprite =
                            std::make_tuple(std::get<1>(asteroide).first,
                                std::get<1>(asteroide).second,
                                std::get<2>(asteroide));
                    createEntityProjectiles(index, pos_dir_sprite);
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_BONUS_COLLISIONS,
            [this](const std::vector<std::any> &args) {
                (void) args;
                std::pair<std::list<size_t>,
                    std::list<
                        std::pair<BONUS, std::tuple<size_t, float, float>>>>
                    list_bonuses = _collision_system.detectCollisionsBonus(
                        _ecs._components_arrays);
                ;
                if (!list_bonuses.first.empty()) {
                    for (auto bonus : list_bonuses.second) {
                        create_bonus(bonus);
                    }
                    for (auto dead_bonus : list_bonuses.first) {
                        _kill_system.killEntity(_ecs, dead_bonus);
                    }
                    send_client_dead_entities(list_bonuses.first);
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_BONUS,
            [this](const std::vector<std::any> &args) {
                (void) args;
                std::list<std::pair<size_t, std::list<BONUS>>> bonuses =
                    _bonus_system.checkBonus(_ecs._components_arrays);

                if (!bonuses.empty()) {
                    for (auto bonus : bonuses) {
                        desactivateBonus(bonus);
                    }
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_LIFE,
            [this](const std::vector<std::any> &args) {
                (void) args;
                std::list<std::pair<size_t, int>> player_life =
                    _health_system.updatePlayerLife(_ecs._components_arrays);

                if (!player_life.empty()) {
                    send_client_player_lifes(player_life);
                }
            });
        _eventBus.subscribe(RTYPE_ACTIONS::CLIENT_LEAVE,
            [this](const std::vector<std::any> &args) {
                try {
                    ecs::udp::Message message = std::any_cast<
                        std::reference_wrapper<ecs::udp::Message>>(args[0])
                                                    .get();

                    remove_player(message.id);
                } catch (const std::bad_any_cast &e) {
                    std::cerr << "Error during event handling: dans" << e.what()
                              << std::endl;
                }
            });
    }
} // namespace rtype