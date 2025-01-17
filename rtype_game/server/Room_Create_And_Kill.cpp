/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room_Create_And_Kill
*/

#include "Room.hpp"

namespace rtype
{
    void Room::createClient(std::string lastclientAdr, std::string clientName)
    {
        std::cout << "Client created in room [" << _name << "] with addr: " << lastclientAdr << std::endl;

        std::string roomAddress = getAddress();

        std::pair<float, float> position = get_player_start_position(getNbClient());

        std::vector<char> send_message;
        ecs::udp::Message mes;
        mes.action = RTYPE_ACTIONS::CREATE_CLIENT;
        mes.params = std::to_string(static_cast<int>(position.first)) + ";" + std::to_string(static_cast<int>(position.second)) + ";" + std::to_string(_gameplay_factory->getPlayerHealth()) + ";" + std::to_string(_port) + ";" + std::to_string(_gameplay_factory->getDifficulty()) + ":" + sendExistingEntities();

        std::cout << "CREATE CLINET : " << mes.params << std::endl;
        mes.id = create_player(position, clientName);
        _message_compressor.serialize(mes, send_message);
        _clientAddresses.push_back(lastclientAdr);
        std::cout << lastclientAdr << std::endl;
        if (_udp_server->sendMessage(send_message, lastclientAdr)) {

            std::cout << "Message sent: " << mes.params << mes.action << std::endl;
        } else {
            std::cerr << "Failed to send message." << std::endl;
        }
        mes.action = RTYPE_ACTIONS::CREATE_TEAMMATE;
        size_t port_pos = mes.params.find(";port=");
        if (port_pos != std::string::npos) {
            mes.params.erase(port_pos);
        }
        _message_compressor.serialize(mes, send_message);
        for (const auto &clientAddr : _clientAddresses) {
            if (clientAddr != lastclientAdr)
                _udp_server->sendMessage(send_message, clientAddr);
        }
        index_ecs++;
    }

    size_t Room::create_player(std::pair<float, float> positions, std::string clientName)
    {
        size_t index = getNextIndex();

        ecs::Direction direction;
        ecs::Playable playable(clientName);
        ecs::Position position(positions.first, positions.second);
        ecs::Velocity velocity(_gameplay_factory->getPlayerVelocity());
        Health health(_gameplay_factory->getPlayerHealth());
        SpriteId spriteId(SPRITES::MY_PLAYER_SHIP);
        Hitbox hitbox(createHitbox(SPRITES::MY_PLAYER_SHIP));
        Allies allies;

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Playable>(index, playable);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<SpriteId>(index, spriteId);
        _ecs.addComponents<Hitbox>(index, hitbox);
        _ecs.addComponents<Allies>(index, allies);
        _ecs.addComponents<Damage>(index, Damage(_gameplay_factory->getPlayerBodyDamage()));
        _ecs.addComponents<PowerUp>(index, PowerUp());

        _nb_client++;

        return index;
    }

    void Room::createEntityProjectiles(size_t index, std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> pos_dir_sprite)
    {
        _ecs.addComponents<ecs::Direction>(index, ecs::Direction(static_cast<ecs::direction>(std::get<1>(pos_dir_sprite).first), static_cast<ecs::direction>(std::get<1>(pos_dir_sprite).second)));
        _ecs.addComponents<ecs::Velocity>(index, _gameplay_factory->getProjectilesVelocity(std::get<2>(pos_dir_sprite)));
        _ecs.addComponents<ecs::Position>(index, ecs::Position(std::get<0>(pos_dir_sprite).first, std::get<0>(pos_dir_sprite).second));
        _ecs.addComponents<Health>(index, _gameplay_factory->getProjectilesHealth(std::get<2>(pos_dir_sprite)));
        _ecs.addComponents<Projectiles>(index, Projectiles());
        _ecs.addComponents<SpriteId>(index, SpriteId(std::get<2>(pos_dir_sprite)));
        _ecs.addComponents<Hitbox>(index, Hitbox(createHitbox(std::get<2>(pos_dir_sprite))));
        _ecs.addComponents<Damage>(index, Damage(_gameplay_factory->getProjectilesDamage(std::get<2>(pos_dir_sprite))));
        if (Utils::isAllie(std::get<2>(pos_dir_sprite))) {
            _ecs.addComponents<Allies>(index, Allies());
        } else {
            _ecs.addComponents<Ennemies>(index, Ennemies());
        }
        std::string projectileInfo = Utils::projectilesInfoToString(pos_dir_sprite, _gameplay_factory->getProjectilesVelocity(std::get<2>(pos_dir_sprite)));
        send_client_new_projectile(index, projectileInfo);
    }

    void Room::createProjectiles(ecs::udp::Message &message)
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = index_ecs;
            index_ecs++;
        }
        std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> pos_dir_type = Utils::extractProjectilePosAndDir(message.params);
        createEntityProjectiles(index, pos_dir_type);
    }

    void Room::createMonster(SPRITES sprites)
    {
        size_t index = getNextIndex();
        std::pair<int, int> positions = std::make_pair(_window_width + 30, _random_number.generateRandomNumbers(20, _window_height - 100));

        _ecs.addComponents<ecs::Position>(index, ecs::Position(positions.first, positions.second));
        _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(_gameplay_factory->getMonsterVelocity(sprites)));
        _ecs.addComponents<Health>(index, Health(_gameplay_factory->getMonsterHealth(sprites)));
        _ecs.addComponents<Monster>(index, Monster(sprites));
        _ecs.addComponents<Hitbox>(index, Hitbox(createHitbox(sprites)));
        _ecs.addComponents<Damage>(index, Damage(_gameplay_factory->getMonsterBodyDamage(sprites)));
        _ecs.addComponents<ecs::Direction>(index, ecs::Direction(ecs::direction::LEFT, ecs::direction::NO_DIRECTION));
        _ecs.addComponents<Ennemies>(index, Ennemies());
        send_client_new_monster(index, positions.first, positions.second, sprites);
    }

    void Room::spawnBonus(const std::pair<float, float> &position)
    {
        size_t index = getNextIndex();

        BONUS bonus = _gameplay_factory->getRandomBonuses(_random_number.generateRandomNumbers(1, BONUS::MAX_BONUS - 1));
        SPRITES sprite = _gameplay_factory->getSpriteBonus(bonus);
        int bonus_speed = _gameplay_factory->getBonusSpeed();

        _ecs.addComponents<ecs::Direction>(index, ecs::Direction(ecs::direction::LEFT, ecs::direction::NO_DIRECTION));
        _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(bonus_speed));
        _ecs.addComponents<ecs::Position>(index, ecs::Position(position.first, position.second));
        _ecs.addComponents<SpriteId>(index, SpriteId(sprite));
        _ecs.addComponents<Hitbox>(index, Hitbox(createHitbox(sprite)));
        _ecs.addComponents<Ennemies>(index, Ennemies());
        _ecs.addComponents<Bonus>(index, Bonus(bonus));

        std::string projectileInfo = Utils::bonusInfoToString(position, ecs::direction::LEFT, ecs::direction::NO_DIRECTION, sprite, bonus_speed);
        send_client_new_projectile(index, projectileInfo);
    }

    void Room::createBoss(SPRITES sprites)
    {
        size_t index = getNextIndex();
        std::pair<int, int> positions = std::make_pair(_window_width + 100, 0);

        _ecs.addComponents<ecs::Position>(index, ecs::Position(positions.first, positions.second));
        _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(_gameplay_factory->getBossVelocity(sprites)));
        _ecs.addComponents<Health>(index, Health(_gameplay_factory->getBossHealth(sprites)));
        _ecs.addComponents<Monster>(index, Monster(sprites, _gameplay_factory->getMonsterScoreValue(sprites)));
        _ecs.addComponents<Hitbox>(index, Hitbox(createHitbox(sprites)));
        _ecs.addComponents<Damage>(index, Damage(_gameplay_factory->getMonsterBodyDamage(sprites)));
        _ecs.addComponents<ecs::Direction>(index, ecs::Direction(ecs::direction::LEFT, ecs::direction::NO_DIRECTION));
        _ecs.addComponents<Ennemies>(index, Ennemies());
        send_client_new_monster(index, positions.first, positions.second, sprites);
    }

    std::pair<int, int> Room::createHitbox(SPRITES id)
    {
        if (id <= 0 || id >= SPRITES::MAX_SPRITE)
            throw std::invalid_argument("Invalid sprite ID in hit box.");
        return SpriteFactory::getMaxTextureSizeForSprite(id);
    }

    void Room::create_bonus(std::pair<BONUS, std::tuple<size_t, float, float>> bonus_info) {

        switch (bonus_info.first)
        {
            case BONUS::LIFE:
                _bonus_system.addPlayerLife(_ecs._components_arrays, std::get<0>(bonus_info.second), _gameplay_factory->getLifeBonus());
                break;
            case BONUS::VELOCITY:
                _bonus_system.changePlayerVelocity(_ecs._components_arrays, std::get<0>(bonus_info.second), _gameplay_factory->getVelocityBoostBonus());
                _bonus_system.powerUp(_ecs._components_arrays, std::get<0>(bonus_info.second), bonus_info.first, _gameplay_factory->getVelocityDurationBonus());
                send_client_change_player_velocity(true);
                break;
            case BONUS::SHIELD:
                _bonus_system.updatePlayerTempShield(_ecs._components_arrays, std::get<0>(bonus_info.second), SpriteFactory::getMaxTextureSizeForSprite(SPRITES::MY_PLAYER_SHIP_SHIELD), true);
                _bonus_system.powerUp(_ecs._components_arrays, std::get<0>(bonus_info.second), bonus_info.first, _gameplay_factory->getShieldDuration());
                send_client_player_shield(std::get<0>(bonus_info.second), true);
                break;
            default:
                break;
        }
    }
}