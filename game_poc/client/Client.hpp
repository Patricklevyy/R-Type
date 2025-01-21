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

    // COMPONENTS

    #include "components/Window.hpp"
    #include "components/TempDisplay.hpp"
    #include "components/Displayable.hpp"
    #include "components/Sprite.hpp"
    #include "components/Music.hpp"
    #include "../shared/components/Levels.hpp"
    #include "../shared/components/Health.hpp"

    // SYSTEMS

    #include "system/UpdateEntitySystem.hpp"
    #include "system/RenderWindow.hpp"
    #include "system/Filter.hpp"
    #include "system/ATH.hpp"
    #include "system/PlayerSystem.hpp"
    #include "system/EventWindow.hpp"
    #include "system/MusicSystem.hpp"
    #include "../shared/system/DirectionSystem.hpp"
    #include "../shared/system/PositionSystem.hpp"
    #include "../shared/system/KillSystem.hpp"

    namespace poc_game
    {
        class SFMLHandler;
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
                 * @brief Sends a signal to the server to indicate that the player is playing.
                 */
                void send_server_playing();

                /**
                 * @brief Sends a signal to the server to indicate that the player is jumping.
                 */
                void send_server_jump();

                /**
                 * @brief Sends a signal to the server to restart the game.
                 */
                void send_server_restart_game();

                /**
                 * @brief Creates a new player shoot entity and sends the corresponding signal to the server.
                 */
                void create_new_player_shoot();

                /**
                 * @brief Handles a mouse click event, triggers associated actions.
                 */
                void handleMouseClick();

                bool _in_menu = true;
                bool _running = true;
                EventBus _eventBus;

            protected:
            private:
                bool is_playing = false;
                bool first = false;
                int _window_width;
                int _window_height;
                std::string _name;
                std::map<int, int> ecs_server_to_client;
                std::map<int, int> ecs_client_to_server;
                std::map<LEVELS, bool> _levels_wins;
                ecs::ECS _ecs;
                std::queue<sf::Event> _events;
                size_t _index_ecs_client = 0;

                // CLASSES

                std::shared_ptr<SFMLHandler> _sfml_handler;
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
                void createPlayer(unsigned int, float, float);

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
                size_t getNextIndex();

                /**
                 * @brief Adds a level status screen.
                 */
                void add_level_status_screen();


                /**
                 * @brief Restarts the game using the data from the server.
                 * @param message The server message containing data to restart the game.
                 */
                void restart_game(ecs::udp::Message&);

                /**
                 * @brief Creates a new projectile entity for the player.
                 * @param server_id The unique identifier assigned to the entity on the server.
                 * @param x The x-coordinate for the projectile's starting position.
                 * @param y The y-coordinate for the projectile's starting position.
                 * @param dir_x The x direction for the projectile's movement.
                 * @param dir_y The y direction for the projectile's movement.
                 * @param velocity The velocity at which the projectile moves.
                 * @param spriteId The ID of the sprite to be used for the projectile.
                 */
                void createEntityProjectile(unsigned int, float, float, int, int, int, int);
                // MESSAGE TO SERVER

                /**
                 * @brief Inform the server that the game has start.
                 */
                void send_server_start_game();

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
                 * @brief Initializes the player with specified parameters.
                 * @param server_id The unique identifier for the player entity on the server.
                 * @param x The initial x coordinate for the player's position.
                 * @param y The initial y coordinate for the player's position.
                 */
                void init_player(unsigned int, float, float);

                /**
                 * @brief Initializes the play button.
                 */
                void init_play_button();

                /**
                 * @brief Initializes the game using data from the server.
                 * @param message The server message containing data to initialize the game.
                 */
                void init_game(ecs::udp::Message &);
        };
    }
#endif /* !CLIENT_HPP_ */
