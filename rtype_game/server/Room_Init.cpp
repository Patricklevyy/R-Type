/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Room_Init
*/

#include "Room.hpp"

namespace rtype
{
    void Room::init_ecs_server_registry()
    {
        _ecs.addRegistry<Health>();
        _ecs.addRegistry<Projectiles>();
        _ecs.addRegistry<SpriteId>();
        _ecs.addRegistry<Monster>();
        _ecs.addRegistry<Hitbox>();
        _ecs.addRegistry<Ennemies>();
        _ecs.addRegistry<Allies>();
        _ecs.addRegistry<Levels>();
    }

    void Room::init_all(int port, std::string window_width, std::string window_height)
    {
        _window_width = std::stoi(window_width);
        _window_height = std::stoi(window_height);
        _port = port;
        _udp_server = std::make_shared<ecs::udp::UDP_Server>();
        _gameplay_factory = std::make_shared<GameplayFactory>();

        _gameplay_factory->init("rtype_game/config/gameplay_config.conf");

        if (!_udp_server->initialize("rtype_game/config/udp_config.conf", port)) {
            std::cerr << "Failed to initialize socket for room " << _name << std::endl;
            return;
        }
        _ecs.init_basic_registry();
        init_ecs_server_registry();
        _udp_server->startReceiving();
        _timer.init("rtype_game/config/server_config.conf", true);
        _game_running = true;
        std::cout << "je suis dans le game thread" << std::endl;
        init_event_bus();
    }
}