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
    #include "RandomNumber.hpp"
    #include "../shared/GameplayFactory.hpp"
    #include "../shared/SpriteFactory.hpp"

    // COMPONENTS

    #include "../shared/components/Health.hpp"
    #include "components/Projectiles.hpp"
    #include "components/Monster.hpp"
    #include "components/SpriteId.hpp"
    #include "components/Hitbox.hpp"
    #include "components/Allies.hpp"
    #include "components/Ennemies.hpp"
    #include "components/Bonus.hpp"
    #include "components/Damage.hpp"
    #include "components/PowerUp.hpp"
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
    #include "system/AsteroideSystem.hpp"
    #include "RandomNumber.hpp"
    #include "system/LevelSystem.hpp"
    #include "../shared/system/KillSystem.hpp"
    #include "../shared/system/BonusSystem.hpp"

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
            void createClient(std::string, std::string);

            /**
             * @brief Retrieves the address of the room.
             * @return The room's address.
             */
            std::string getAddress() const;


            /**
             * @brief Sends the existing entities in the room to the clients.
             * @return A string containing the serialized data of the existing entities.
             */
            std::string sendExistingEntities();

            void spawnBonus(const std::pair<float, float> &position);
            std::vector<std::string> _clientAddresses;


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
            bool playingInLevel = false;
            unsigned int _nb_client = 0;
            int _sockfd;
            struct sockaddr_in _addr;
            std::thread _gameThread;
            RandomNumber _random_number;
            std::shared_ptr<GameplayFactory> _gameplay_factory;

            // SYSTEMS

            PositionSystem _positon_system;
            DirectionSystem _direction_system;
            BoundariesSystem _boundaries_system;
            MonsterMovementSystem _monster_movement_system;
            CollisionSystem _collision_system;
            HealthSystem _health_system;
            ShootingSystem _shooting_system;
            LevelSystem _level_system;
            KillSystem _kill_system;
            AsteroideSystem _asteroide_system;
            BonusSystem _bonus_system;

            /**
             * @brief Sends information about dead entities to clients.
             * @param deadEntities A list of IDs for the dead entities.
             */
            void send_client_dead_entities(std::list<size_t>);

            /**
             * @brief Initializes the event bus for the room.
             */
            void init_event_bus();

            void init_all(int, std::string, std::string, std::string);

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

            /**
             * @brief Creates a new monster entity.
             * @param sprite The sprite ID of the monster.
             */
            void createMonster(SPRITES);

            /**
             * @brief Creates a new boss entity.
             * @param sprite The sprite ID of the boss.
             */
            void createBoss(SPRITES);

            /**
             * @brief Sends information about a new monster to a client.
             * @param entityId The ECS ID of the monster.
             * @param x The x position of the monster.
             * @param y The y position of the monster.
             * @param sprite The sprite ID of the monster.
             */
            void send_client_new_monster(size_t, float, float , int);

            /**
             * @brief Returns the next available index for a new entity.
             * 
             * @return The index of the next available entity.
             */
            size_t getNextIndex();

            /**
             * @brief Starts the level with a specific difficulty or settings.
             * 
             * @param level The level to be started.
             */
            void startLevel(LEVELS level);

            /**
             * @brief Sends the client the status of a specific level.
             * 
             * @param status The status of the level (true or false).
             * @param level The level to send the status for.
             */
            void send_client_level_status(bool status, LEVELS level);

            /**
             * @brief Sends a message to the server to start the level.
             */
            void send_client_start_level();

            /**
             * @brief Sends the current score to the server.
             * 
             * @param score The player's current score to send.
             */
            void sendScore(unsigned int score);

            /**
             * @brief Sends a request to roll back an action or state.
             */
            void send_roll_back();

            /**
             * @brief Creates a hitbox for a sprite.
             * 
             * @param sprite The sprite for which the hitbox will be created.
             * @return A pair containing the hitbox width and height.
             */
            std::pair<int, int> createHitbox(SPRITES sprite);

            /**
             * @brief Creates a bonus entity with additional data.
             * 
             * @param bonus A pair containing the bonus type and its additional data (id, x, y).
             */
            void create_bonus(std::pair<BONUS, std::tuple<size_t, float, float>> bonus);

            /**
             * @brief Sends the client a request to change the player's velocity.
             * 
             * @param playerId The player id whose velocity is to be changed.
             * @param isIncreasing Whether the velocity should be increased or decreased.
             */
            void send_client_change_player_velocity(size_t playerId, bool isIncreasing);

            /**
             * @brief Sends the client a request to toggle the player's shield state.
             * 
             * @param playerId The player id whose shield state is to be toggled.
             * @param isActive Whether the shield is activated or deactivated.
             */
            void send_client_player_shield(size_t playerId, bool isActive);

            /**
             * @brief Deactivates a specific bonus for a player.
             * 
             * @param player A pair containing the player id and the list of bonuses to deactivate.
             */
            void desactivateBonus(std::pair<size_t, std::list<BONUS>> player);

            /**
             * @brief Sends the client the updated life values for multiple players.
             * 
             * @param playerLives A list of player ids and their updated life values.
             */
            void send_client_player_lifes(std::list<std::pair<size_t, int>> playerLives);
            
            /**
             * @brief Sends the client a request to change the player's weapon.
             * 
             * @param playerId The player id whose weapon is to be changed.
             * @param put Whether the weapon should be put or removed.
             */
            void send_client_player_weapon(size_t index, bool put);
        };
    }

#endif /* !ROOM_HPP_ */
