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
        mes.params = std::to_string(static_cast<int>(position.first)) + ";" + std::to_string(static_cast<int>(position.second)) + ";" + std::to_string(_port) + ":" + sendExistingEntities();

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
        ecs::Velocity velocity(200);
        Health health(100);
        SpriteId spriteId(SPRITES::MY_PLAYER_SHIP);
        Hitbox hitbox(HitboxFactory::createHitbox(SPRITES::MY_PLAYER_SHIP));
        Allies allies;

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Playable>(index, playable);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<SpriteId>(index, spriteId);
        _ecs.addComponents<Hitbox>(index, hitbox);
        _ecs.addComponents<Allies>(index, allies);

        _nb_client++;

        return index;
    }

    void Room::createEnemiesProjectiles(size_t index, std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> pos_dir_sprite)
    {
        ecs::Direction direction(static_cast<ecs::direction>(std::get<1>(pos_dir_sprite).first), static_cast<ecs::direction>(std::get<1>(pos_dir_sprite).second));
        ecs::Position position(std::get<0>(pos_dir_sprite).first, std::get<0>(pos_dir_sprite).second);
        ecs::Velocity velocity(300);
        Health health(20);
        Hitbox hitbox(HitboxFactory::createHitbox(std::get<2>(pos_dir_sprite)));
        Projectiles projectile;
        SpriteId spriteId(std::get<2>(pos_dir_sprite));
        Ennemies enemmies;

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Projectiles>(index, projectile);
        _ecs.addComponents<SpriteId>(index, spriteId);
        _ecs.addComponents<Hitbox>(index, hitbox);
        _ecs.addComponents<Ennemies>(index, enemmies);
        send_client_new_projectile(index, std::get<0>(pos_dir_sprite).first, std::get<0>(pos_dir_sprite).second, std::get<2>(pos_dir_sprite));
    }

    void Room::createEntityProjectiles(size_t index, std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> pos_dir_sprite)
    {
        ecs::Direction direction(static_cast<ecs::direction>(std::get<1>(pos_dir_sprite).first), static_cast<ecs::direction>(std::get<1>(pos_dir_sprite).second));
        ecs::Position position(std::get<0>(pos_dir_sprite).first, std::get<0>(pos_dir_sprite).second);
        ecs::Velocity velocity(300);
        Health health(20);
        Hitbox hitbox(HitboxFactory::createHitbox(std::get<2>(pos_dir_sprite)));
        Projectiles projectile;
        SpriteId spriteId(std::get<2>(pos_dir_sprite));
        Allies allies;

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Projectiles>(index, projectile);
        _ecs.addComponents<SpriteId>(index, spriteId);
        _ecs.addComponents<Hitbox>(index, hitbox);
        _ecs.addComponents<Allies>(index, allies);
        send_client_new_projectile(index, std::get<0>(pos_dir_sprite).first, std::get<0>(pos_dir_sprite).second, std::get<2>(pos_dir_sprite));
    }

    void Room::createAlliesProjectile(ecs::udp::Message &message)
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
        std::pair<int, int> positions = MonsterFactory::getMonsterSpawnCoordinates(_window_width, _window_height, _random_number);

        _ecs.addComponents<ecs::Position>(index, ecs::Position(positions.first, positions.second));
        _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(MonsterFactory::getMonsterVelocity(sprites)));
        _ecs.addComponents<Health>(index, Health(MonsterFactory::getMonsterLife(sprites)));
        _ecs.addComponents<Monster>(index, Monster(sprites));
        _ecs.addComponents<Hitbox>(index, Hitbox(HitboxFactory::createHitbox(sprites)));
        _ecs.addComponents<ecs::Direction>(index, ecs::Direction(ecs::direction::LEFT, ecs::direction::NO_DIRECTION));
        _ecs.addComponents<Ennemies>(index, Ennemies());

        send_client_new_monster(index, positions.first, positions.second, sprites);
    }
}