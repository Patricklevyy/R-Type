/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

#ifndef ROOM_HPP_
    #define ROOM_HPP_

    // INCLUDES

    #include "../shared/Includes.hpp"
    #include "../../ecs/Includes_ecs.hpp"

    // CLASSES

    #include "MessageChecker.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Server.hpp"
    #include "../../ecs/ECS.hpp"
    #include "../shared/EventBus.hpp"
    #include "../shared/Timer.hpp"
    #include "../shared/Utils.hpp"
    #include "HitboxFactory.hpp"
    #include "RandomNumber.hpp"

    // COMPONENTS

    #include "../shared/components/Health.hpp"
    #include "components/Projectiles.hpp"
    #include "components/Monster.hpp"
    #include "components/SpriteId.hpp"
    #include "components/Hitbox.hpp"
    #include "components/Allies.hpp"
    #include "components/Ennemies.hpp"

    // SYSTEMS

    #include "system/BoundariesSystem.hpp"
    #include "system/MonsterMovementSystem.hpp"
    #include "../../ecs/system/PositionSystem.hpp"
    #include "../../ecs/components/Direction.hpp"
    #include "../shared/system/DirectionSystem.hpp"
    #include "system/CollisionSystem.hpp"
    #include "system/ShootingSystem.hpp"
    #include "system/HealthSystem.hpp"
    #include "RandomNumber.hpp"

    namespace rtype
    {
        class Room
        {
        public:
            Room(int port, const std::string &name);
            ~Room();

            void start(int, std::string, std::string, std::string, std::string);

            void gameThreadFunction(int, std::string, std::string, std::string, std::string);

            bool sendMessage(const std::string &);

            unsigned int getNbClient() const;
            void setNbClient(unsigned int);

            Room(const Room &) = delete;
            Room(Room &&other) noexcept;
            Room &operator=(const Room &) = delete;
            Room &operator=(Room &&other) noexcept;

            std::string getName() const;
            void createClient(std::string, std::string);
            std::string getAddress() const;

            void init_event_bus();
            std::string sendExistingEntities();


        private:
            int _window_width = 0;
            int _window_height = 0;
            Timer _timer;
            int _port;
            unsigned int index_ecs = 0;
            std::shared_ptr<ecs::udp::UDP_Server> _udp_server;
            ecs::udp::MessageCompressor _message_compressor;
            bool _game_running;
            ecs::ECS _ecs;
            EventBus _eventBus;
            std::string _name;
            unsigned int _nb_client;
            int _sockfd;
            struct sockaddr_in _addr;
            std::thread _gameThread;
            std::vector<std::string> _clientAddresses;
            RandomNumber _random_number;

            // SYSTEMS

            ecs::PositionSystem _positon_system;
            rtype::DirectionSystem _direction_system;
            BoundariesSystem _boundaries_system;
            MonsterMovementSystem _monster_movement_system;
            CollisionSystem _collision_system;
            HealthSystem _health_system;
            ShootingSystem _shooting_system;

            void send_client_dead_entities(std::list<size_t>);
            bool initializeSocket();
            void closeRoom();
            void init_ecs_server_registry();
            std::pair<float, float> get_player_start_position(int);
            size_t create_player(std::pair<float, float>, std::string);
            void handleCommand(const std::vector<char> &, std::string clientAddr);
            void sendUpdate();
            void send_client_new_projectile(size_t, float, float, SPRITES);
            void createAlliesProjectile(ecs::udp::Message&);
            void createEntityProjectiles(size_t, std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES>);
            void createMonster();
            void send_client_new_monster(size_t, float, float , int);
        };
    }

#endif /* !ROOM_HPP_ */
