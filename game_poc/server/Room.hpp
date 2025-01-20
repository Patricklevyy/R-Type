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
    #include "PipeFactory.hpp"

    // COMPONENTS

    // #include "../shared/components/Health.hpp"
    // #include "components/Projectiles.hpp"
    // #include "components/Monster.hpp"
    // #include "components/SpriteId.hpp"
    #include "components/Hitbox.hpp"
    #include "components/Allies.hpp"
    #include "components/Ennemies.hpp"
    // #include "../shared/components/Levels.hpp"

    // SYSTEMS

    #include "system/BoundariesSystem.hpp"
    #include "../shared/system/PositionSystem.hpp"
    // #include "../../ecs/components/Direction.hpp"
    #include "../shared/system/DirectionSystem.hpp"
    #include "../shared/system/VelocitySystem.hpp"
    #include "../shared/system/GravitySystem.hpp"
    #include "system/CollisionSystem.hpp"
    // #include "system/ShootingSystem.hpp"
    // #include "system/HealthSystem.hpp"
    // #include "RandomNumber.hpp"
    // #include "system/LevelSystem.hpp"
    // #include "system/ScoreSystem.hpp"
    #include "../shared/system/KillSystem.hpp"

    namespace poc_game
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
            void start(int, std::string, std::string, std::string);

            /**
             * @brief Handles the game thread functionality.
             */
            void gameThreadFunction(int, std::string, std::string, std::string);

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
            void create_client(std::string);

            /**
             * @brief Retrieves the address of the room.
             * @return The room's address.
             */
            std::string getAddress() const;

            /**
             * @brief Initializes the event bus for the room.
             */
            void init_event_bus();

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
            bool isPlaying = false;
            struct sockaddr_in _addr;
            std::thread _gameThread;
            std::vector<std::string> _clientAddresses;
            RandomNumber _random_number;
            std::chrono::time_point<std::chrono::steady_clock> _last_spawn_time;
            constexpr static float PIPE_SPAWN_INTERVAL = 3.0f;

            // SYSTEMS

            PositionSystem _positon_system;
            DirectionSystem _direction_system;
            VelocitySystem _velocity_system;
            GravitySystem _gravity_system;
            BoundariesSystem _boundaries_system;
            KillSystem _kill_system;
            CollisionSystem _collision_system;
            // HealthSystem _health_system;
            // ShootingSystem _shooting_system;
            // LevelSystem _level_system;
            // ScoreSystem _score_system;

            void send_client_positions_update();

            /**
             * @brief Sends information about dead entities to clients.
             * @param deadEntities A list of IDs for the dead entities.
             */
            void send_client_dead_entities(std::list<size_t>);

            void send_client_new_pipe(size_t, float, float y, SPRITES);

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
             * @brief Sends information about losing the game to clients.
             */
            void send_client_loose_game();

            /**
             * @brief Retrieves the next available index.
             * @return The next available index.
             */
            size_t getNextIndex();

            /**
             * @brief Creates a player entity.
             * @param position The position of the player.
             * @return The ID of the created player.
             */
            size_t create_player(std::pair<float, float> position);

            /**
             * @brief Handles a command received from a client.
             * @param command The command data.
             * @param clientAddress The address of the client.
             */
            void handleCommand(const std::vector<char> &command, std::string clientAddress);

            /**
             * @brief Starts the game.
             */
            void start_game();

            /**
             * @brief Makes the player jump.
             */
            void player_jump();

            /**
             * @brief Restarts the game.
             */
            void restart_game();

            /**
             * @brief Sends information about creating a player to clients.
             */
            void send_client_create_player();

            /**
             * @brief Spawns pipes in the game.
             */
            void spawn_pipes();
        };
    }

#endif /* !ROOM_HPP_ */
