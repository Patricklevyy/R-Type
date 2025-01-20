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
                 * @brief Changes the direction of the player.
                 * 
                 * @param oldDir The player's current direction.
                 * @param newDir The player's new direction.
                 */
                void change_player_direction(ecs::direction oldDir, ecs::direction newDir);

                /**
                 * @brief Sends a request to the server to create a new room.
                 * 
                 * @param roomName The name of the room.
                 */
                void send_server_create_room(std::string roomName);

                /**
                 * @brief Sends a request to the server to join an existing room.
                 * 
                 * @param roomName The name of the room.
                 * @param clientName The client's name.
                 */
                void send_server_join_room(std::string roomName, std::string clientName);

                /**
                 * @brief Sets the display filter for the game window.
                 * 
                 * @param filter The filter mode to set.
                 */
                void set_window_filter(FILTER_MODE filter);

                /**
                 * @brief Creates a new player shoot action in the game.
                 */
                void create_new_player_shoot();

                /**
                 * @brief Handles mouse button press events.
                 */
                void handleMousePress();

                /**
                 * @brief Handles mouse button release events.
                 */
                void handleMouseRelease();

                /**
                 * @brief Changes the game's difficulty level.
                 * 
                 * @param difficulty The new difficulty setting.
                 */
                void changeDifficulty(DIFFICULTY difficulty);

                /**
                 * @brief Launches the main menu of the game.
                 */
                void launchMenu();

                bool _in_menu = true;
                bool _running = true;
                EventBus _eventBus;
                ecs::ECS _ecs;
                FILTER_MODE _currentFilter = FILTER_MODE::Neutral;

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
                int _isBoosted = false;
                std::string _name;
                std::map<int, int> ecs_server_to_client;
                std::map<int, int> ecs_client_to_server;
                std::map<LEVELS, bool> _levels_wins;
                std::queue<sf::Event> _events;
                size_t _index_ecs_client = 0;
                std::shared_ptr<GameplayFactory> _gameplay_factory;
                DIFFICULTY _difficulty = DIFFICULTY::EASY;

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
                 * @brief Sends a message to the server to shoot.
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
                 * @brief Gets the index of the next entity.
                 * 
                 * @return The next available index.
                 */
                size_t getNextIndex();

                /**
                 * @brief Adds the level status to the screen.
                 * 
                 * @param status The status to display (true/false).
                 * @param message The UDP message containing the status data.
                 */
                void add_level_status_screen(bool status, ecs::udp::Message &message);

                /**
                 * @brief Restarts the game to its initial state.
                 */
                void restart_game();

                /**
                 * @brief Sends a message to the server to create a new player.
                 */
                void send_server_new_player();

                /**
                 * @brief Creates a new projectile entity in the game.
                 * 
                 * @param id The entity ID.
                 * @param x The x-coordinate of the projectile.
                 * @param y The y-coordinate of the projectile.
                 * @param velocityX The velocity on the X-axis.
                 * @param velocityY The velocity on the Y-axis.
                 * @param direction The projectile's direction.
                 * @param type The type of the projectile.
                 */
                void createEntityProjectile(unsigned int id, float x, float y, int velocityX, int velocityY, int direction, int type);

                /**
                 * @brief Resets the level lock state.
                 */
                void reset_level_lock();

                /**
                 * @brief Sets a lock for a specific level.
                 * 
                 * @param level The level to lock.
                 * @param x The x-coordinate of the lock position.
                 * @param y The y-coordinate of the lock position.
                 */
                void put_level_lock(LEVELS level, int x, int y);

                /**
                 * @brief Initializes the score for the game.
                 */
                void init_score();

                /**
                 * @brief Initializes the life for the game.
                 */
                void init_life();

                /**
                 * @brief Parses a room list string into a vector of room names and player counts.
                 * 
                 * @param roomList The raw string containing the room data.
                 * @return A vector of pairs where each pair contains a room name and its player count.
                 */
                std::vector<std::pair<std::string, int>> parseRoomList(const std::string &roomList);

                /**
                 * @brief Sends a message to the server to start the game with a specific level.
                 * 
                 * @param level The level to start the game at.
                 */
                void send_server_start_game(LEVELS level);

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
                 * @brief Initializes the levels sprites.
                 */
                void init_levels_sprites();

                /**
                 * @brief Execute the animation of levels.
                 */
                void execute_animation();

                /**
                 * @brief Update the health of the player.
                 */
                void updatePlayerLife(std::string);
        };
    }
#endif /* !CLIENT_HPP_ */
