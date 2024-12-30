/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

/**
 * @file Room.hpp
 * @brief Manages game rooms and handles gameplay logic.
 */

#ifndef ROOM_HPP_
    #define ROOM_HPP_

    // INCLUDES

    #include "../shared/Includes.hpp"
    #include "../../ecs/Includes_ecs.hpp"

    // CLASSES

    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Server.hpp"
    #include "../../ecs/ECS.hpp"
    #include "../shared/EventBus.hpp"
    #include "../shared/Timer.hpp"
    #include "../shared/Utils.hpp"
    #include "HitboxFactory.hpp"
    #include "RandomNumber.hpp"
    #include "MonsterFactory.hpp"

    // COMPONENTS

    #include "../shared/components/Health.hpp"
    #include "components/Projectiles.hpp"
    #include "components/Monster.hpp"
    #include "components/SpriteId.hpp"
    #include "components/Hitbox.hpp"
    #include "components/Allies.hpp"
    #include "components/Ennemies.hpp"
    #include "../shared/components/Levels.hpp"

    // SYSTEMS

    #include "system/BoundariesSystem.hpp"
    #include "system/MonsterMovementSystem.hpp"
    #include "../shared/system/PositionSystem.hpp"
    #include "../../ecs/components/Direction.hpp"
    #include "../shared/system/DirectionSystem.hpp"
    #include "system/CollisionSystem.hpp"
    #include "system/ShootingSystem.hpp"
    #include "system/HealthSystem.hpp"
    #include "RandomNumber.hpp"
    #include "system/LevelSystem.hpp"
    #include "system/ScoreSystem.hpp"
    #include "../shared/system/KillSystem.hpp"

    namespace rtype
    {
        /**
        * @class Room
        * @brief Represents a game room with associated entities, systems, and gameplay logic.
        */
        class Room
        {
        public:

            /**
             * @brief Constructs a Room with a given port and name.
             * @param port The port for the room's server.
             * @param name The name of the room.
             */
            Room(int port, const std::string &name);

            /**
             * @brief Destructor for Room.
             */
            ~Room();

            /**
             * @brief Starts the game in the room.
             */
            void start(int, std::string, std::string);

            /**
             * @brief Handles the game thread functionality.
             */
            void gameThreadFunction(int, std::string, std::string);

            /**
             * @brief Sends a message to all clients in the room.
             * @param message The message to send.
             * @return True if the message was sent successfully, false otherwise.
             */
            bool sendMessage(const std::string &);

            /**
             * @brief Retrieves the number of connected clients.
             * @return The number of connected clients.
             */
            unsigned int getNbClient() const;

            /**
             * @brief Sets the number of connected clients.
             * @param nb The new number of clients.
             */
            void setNbClient(unsigned int);

            Room(const Room &) = delete;
            Room(Room &&other) noexcept;
            Room &operator=(const Room &) = delete;
            Room &operator=(Room &&other) noexcept;


            /**
             * @brief Retrieves the name of the room.
             * @return The name of the room.
             */
            std::string getName() const;

            /**
             * @brief Creates a new client for the room.
             * @param ip The IP address of the client.
             * @param name The name of the client.
             */
            void createClient(std::string, std::string);

            /**
             * @brief Retrieves the address of the room.
             * @return The room's address.
             */
            std::string getAddress() const;

            /**
             * @brief Initializes the event bus for the room.
             */
            void init_event_bus();

            /**
             * @brief Sends the existing entities in the room to the clients.
             * @return A string containing the serialized data of the existing entities.
             */
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
            unsigned int _nb_client = 0;
            int _sockfd;
            struct sockaddr_in _addr;
            std::thread _gameThread;
            std::vector<std::string> _clientAddresses;
            RandomNumber _random_number;

            // SYSTEMS

            PositionSystem _positon_system;
            DirectionSystem _direction_system;
            BoundariesSystem _boundaries_system;
            MonsterMovementSystem _monster_movement_system;
            CollisionSystem _collision_system;
            HealthSystem _health_system;
            ShootingSystem _shooting_system;
            LevelSystem _level_system;
            ScoreSystem _score_system;
            KillSystem _kill_system;

            /**
             * @brief Sends information about dead entities to clients.
             * @param deadEntities A list of IDs for the dead entities.
             */
            void send_client_dead_entities(std::list<size_t>);

            /**
             * @brief Initializes the room's network socket.
             * @return True if the socket was initialized successfully, false otherwise.
             */
            bool initializeSocket();

            /**
             * @brief Closes the room and cleans up resources.
             */
            void closeRoom();

             /**
             * @brief Initializes the ECS server registry.
             */
            void init_ecs_server_registry();

            /**
             * @brief Retrieves the starting position for a player.
             * @param playerIndex The index of the player.
             * @return A pair representing the x and y coordinates of the start position.
             */
            std::pair<float, float> get_player_start_position(int);

            /**
             * @brief Creates a player entity in the ECS.
             * @param position The starting position of the player.
             * @param sprite The sprite ID of the player.
             * @return The ECS ID of the created player entity.
             */
            size_t create_player(std::pair<float, float>, std::string);

             /**
             * @brief Handles a command sent by a client.
             * @param command The raw command data.
             * @param clientAddr The address of the client sending the command.
             */
            void handleCommand(const std::vector<char> &, std::string clientAddr);

            /**
             * @brief Sends updates to all clients about the current game state.
             */
            void send_client_positions_update();

            /**
             * @brief Sends information about a new projectile to a client.
             * @param entityId The ECS ID of the projectile.
             * @param x The x position of the projectile.
             * @param y The y position of the projectile.
             * @param sprite The sprite ID of the projectile.
             */
            void send_client_new_projectile(size_t, std::string&);

            /**
            * @brief Creates a new projectile for an allied entity.
            * @param message The message containing projectile data.
            */
            void createProjectiles(ecs::udp::Message&);

            /**
             * @brief Creates projectiles for a specific entity.
             * @param entityId The ID of the entity creating the projectile.
             * @param data The position, hitbox, and sprite data for the projectile.
             */
            void createEntityProjectiles(size_t, std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES>);

            void createMonster(SPRITES);
            void send_client_new_monster(size_t, float, float , int);
            size_t getNextIndex();
            void startLevel(LEVELS);
            void send_client_level_status(bool, LEVELS);
            void send_client_remove_ath();
        };
    }

#endif /* !ROOM_HPP_ */
