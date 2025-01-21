/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

/**
 * @file Client.hpp
 * @brief Class representing the client for the game.
 * The `Client` class handles all the client-side logic of the game, such as communication
 * with the server, event handling, entity management, and window rendering.
 */

#ifndef CLIENT_HPP_
    #define CLIENT_HPP_

    // INCLUDES

    #include "../shared/Includes.hpp"
    #include "../../ecs/Structures_ecs.hpp"

    // CLASSES

    #include "SFMLHandler.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Client.hpp"
    #include "../../ecs/ECS.hpp"
    #include "../shared/EventBus.hpp"
    #include "../shared/Timer.hpp"
    #include "../shared/Utils.hpp"
    #include "../shared/GameplayFactory.hpp"

    // COMPONENTS

    #include "components/Window.hpp"
    #include "components/LevelStatus.hpp"
    #include "components/Displayable.hpp"
    #include "components/Sprite.hpp"
    #include "components/Music.hpp"
    #include "components/Animation.hpp"
    #include "../shared/components/Levels.hpp"
    #include "../shared/components/Health.hpp"
    #include "components/Text.hpp"
    #include "components/Life.hpp"

    // SYSTEMS

    #include "system/UpdateEntitySystem.hpp"
    #include "system/RenderWindow.hpp"
    #include "system/Filter.hpp"
    #include "system/ATH.hpp"
    #include "system/PlayerSystem.hpp"
    #include "system/EventWindow.hpp"
    #include "system/MusicSystem.hpp"
    #include "system/ScoreSystem.hpp"
    #include "system/AnimationSystem.hpp"
    #include "../shared/system/DirectionSystem.hpp"
    #include "../shared/system/PositionSystem.hpp"
    #include "../shared/system/KillSystem.hpp"
    #include "../shared/system/BonusSystem.hpp"

    #include "menu/Menu.hpp"

    namespace rtype
    {
        class SFMLHandler;
        class Menu;
        /**
         * @class Client
         * @brief Handle the client actions.
         */
        class Client
        {
            public:
                /**
                 * @brief Default constructor for the Client class.
                 */
                Client();
                /**
                 * @brief Destructor for the Client class.
                 */
                ~Client();

                /**
                 * @brief Starts the game client.
                 */
                void start();

                /**
                 * @brief Handles messages from the server.
                 * @param message A vector of characters representing the message from the server.
                 */
                void handle_message(std::vector<char>&);

                /**
                 * @brief Modify the direction of the player.
                 * @param horizontal The horizontal direction of the player.
                 * @param vertical The vertical direction of the player.
                 */
                void change_player_direction(ecs::direction, ecs::direction);

                /**
                 * @brief Sends a request to the server to create a new room.
                 * @param roomName The name of the room to be created.
                 */
                void send_server_create_room(std::string roomName);

                /**
                 * @brief Sends a request to the server to join an existing room.
                 * @param roomName The name of the room to join.
                 * @param clientName The name of the client joining the room.
                 */
                void send_server_join_room(std::string roomName, std::string clientName);

                /**
                 * @brief Sets the window's filter mode.
                 * @param filterMode The filter mode to apply to the window.
                 */
                void set_window_filter(FILTER_MODE);

                /**
                 * @brief Creates a new player shot entity in the game.
                 */
                void create_new_player_shoot();

                /**
                 * @brief Handles the mouse press event.
                 */
                void handleMousePress();

                /**
                 * @brief Handles the mouse release event.
                 */
                void handleMouseRelease();

                /**
                 * @brief Changes the game's difficulty level.
                 * @param difficulty The new difficulty level to set.
                 */
                void changeDifficulty(DIFFICULTY);


                /**
                 * @brief Launches the game's main menu.
                 */
                void launchMenu();


                bool _in_menu = true;
                bool _running = true;
                EventBus _eventBus;
                ecs::ECS _ecs;
                FILTER_MODE _currentFilter = FILTER_MODE::Neutral;
                DIFFICULTY _difficulty = DIFFICULTY::EASY;

                /**
                 * @brief Sends a message to the server to ask the list of all the rooms.
                 */
                void requestRoomList();

                std::mutex roomListMutex;
                std::vector<std::pair<std::string, int>> _roomsList;
                std::shared_ptr<SFMLHandler> _sfml_handler;


            protected:
            private:
                int _window_width;
                int _window_height;
                bool _inLevelStatus = false;
                int _isBoosted = false;
                std::string _name;
                std::map<int, int> ecs_server_to_client;
                std::map<int, int> ecs_client_to_server;
                std::map<LEVELS, bool> _levels_wins;
                std::queue<sf::Event> _events;
                size_t _index_ecs_client = 0;
                std::shared_ptr<GameplayFactory> _gameplay_factory;
                // DIFFICULTY _difficulty = DIFFICULTY::EASY;

                // CLASSES

                ecs::udp::MessageCompressor _message_compressor;
                std::shared_ptr<Timer> _timer;
                std::shared_ptr<ecs::udp::UDP_Client> _udpClient;

                // SYSTEMS

                EventWindow _event_window_system;
                DirectionSystem _direction_system;
                PositionSystem _position_system;
                RenderWindow _render_window_system;
                Filter _filter_system;
                UpdateEntitySystem _update_entity_system;
                ATH _ath_system;
                KillSystem _kill_system;
                PlayerSystem _player_system;
                MusicSystem _music_system;
                ScoreSystem _score_system;
                AnimationSystem _animation_system;
                BonusSystem _bonus_system;

                /**
                 * @brief Sends a new shoot event to the server.
                 * @param charged A boolean value that indicates if the shot is charged.
                 */
                void send_server_new_shoot(bool charged = false);

                bool _mouse_pressed = false;
                std::chrono::steady_clock::time_point _mouse_press_time;


                /**
                 * @brief Kills the entities specified by the given list of entity indices.
                 * @param entities A list of entity indices to be killed.
                 */
                void killEntity(std::list<size_t>);

                /**
                 * @brief Sets the room address for the game client.
                 * @param roomAddress The address of the room to connect to.
                 */
                void setRoomAdress(int);

                /**
                 * @brief Creates a player entity with the specified parameters.
                 * @param id The unique identifier for the player.
                 * @param x The initial x-coordinate of the player.
                 * @param y The initial y-coordinate of the player.
                 */
                void createPlayer(unsigned int, float, float, int);

                /**
                 * @brief Sends a message to the server with the player's direction.
                 * @param direction The player's current direction.
                 * @param lastDirection The player's previous direction.
                */
                void send_server_player_direction(ecs::direction, ecs::direction);

                /**
                 * @brief Initializes the game with the given message.
                 * @param message The initialization message from the server.
                 */
                void init_game(ecs::udp::Message &);

                /**
                 * @brief Creates a new entity with the specified parameters.
                 * @param id The entity's unique identifier.
                 * @param x The entity's x-coordinate.
                 * @param y The entity's y-coordinate.
                 * @param sprite The sprite identifier for the entity.
                 */
                void createEntity(unsigned int, float, float, SPRITES);

                /**
                 * @brief Creates a new projectile entity.
                 * @param message The message from the server containing the projectile data.
                 */
                void createProjectile(ecs::udp::Message&);

                /**
                 * @brief Updates entities during the first connection.
                 * @param message The message containing the update data.
                 */
                void updateEntitiesFirstConnexion(const std::string &);

                /**
                 * @brief Gets the next available index for a new entity or object.
                 */
                size_t getNextIndex();

                /**
                 * @brief Adds a level status screen based on certain conditions.
                 * @param condition A boolean value indicating whether to show or hide the level status.
                 * @param message A reference to a Message object containing the information to display.
                 */
                void add_level_status_screen(bool, ecs::udp::Message &);

                /**
                 * @brief Restarts the game, resetting necessary variables and components.
                 */
                void restart_game();

                /**
                 * @brief Sends a request to the server to create a new player.
                 */
                void send_server_new_player();

                /**
                 * @brief Creates a new projectile entity with the given parameters.
                 * @param server_id The unique identifier for the projectile on the server side.
                 * @param x The x coordinate for the projectile's starting position.
                 * @param y The y coordinate for the projectile's starting position.
                 * @param dir_x The x-direction for the projectile's movement.
                 * @param dir_y The y-direction for the projectile's movement.
                 * @param velocity The speed at which the projectile moves.
                 * @param spriteId The sprite ID representing the projectile's visual appearance.
                 */
                void createEntityProjectile(unsigned int, float, float, int, int, int, int);

                /**
                 * @brief Resets the level lock, allowing the level to be modified again.
                 */
                void reset_level_lock();

                /**
                 * @brief Sets a lock on the level.
                 * @param level The level to lock.
                 * @param x The x-coordinate associated with the level lock.
                 * @param y The y-coordinate associated with the level lock.
                 */
                void put_level_lock(LEVELS, int, int);


                /**
                 * @brief Initializes the score for the game.
                 */
                void init_score();

                /**
                 * @brief Initializes the player's life or health.
                 */
                void init_life();

                /**
                 * @brief Parses a list of room names and their respective IDs.
                 * @param roomList A string representing the raw list of rooms to be parsed.
                 */
                std::vector<std::pair<std::string, int>> parseRoomList(const std::string &);


                /**
                 * @brief Sends a request to the server to start the game with the specified level.
                 * @param level The level to start the game with.
                 */
                void send_server_start_game(LEVELS);

                // INITIALISATION

                /**
                 * @brief Initializes all components of the client.
                 */
                void init_all();

                /**
                 * @brief Initializes the window size based on the provided configuration.
                 * @param config A string containing the configuration for the window size.
                 */
                void init_window_size(const std::string&);

                /**
                 * @brief Initializes the game window and background.
                 */
                void init_window_and_background();

                /**
                 * @brief Initializes the ECS client registry.
                 */
                void init_ecs_client_registry();

                /**
                 * @brief Initializes the event bus subscription.
                 */
                void init_subscribe_event_bus();

                /**
                 * @brief Initializes the sprites for the levels.
                 */
                void init_levels_sprites();

                /**
                 * @brief Executes the animations for the game.
                 */
                void execute_animation();

                /**
                 * @brief Updates the player's life and health display.
                 * @param lifes_string The new health value of the player.
                 */
                void updatePlayerLife(std::string);

                /**
                 * @brief Handles the time-related behavior for level status.
                 */
                void levelStatusTime();
        };
    }
#endif /* !CLIENT_HPP_ */
