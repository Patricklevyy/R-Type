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

        /**
         * @class Client
         * @brief Represents the game client.
         */
        class SFMLHandler;
        class Client
        {
            public:
                /**
                 * @brief Default constructor for the Client class.
                 * 
                 * Initializes the client object. This constructor sets up the necessary
                 * data structures and prepares the client for use.
                 */
                Client();

                /**
                 * @brief Destructor for the Client class.
                 * 
                 * Cleans up resources used by the client before it is destroyed.
                 * This includes closing any open connections and releasing allocated memory.
                 */
                ~Client();

                /**
                 * @brief Starts the game client.
                 * 
                 * This function initializes all game-related components and starts the
                 * communication with the server to begin the game.
                 */
                void start();

                /**
                 * @brief Handles messages received from the server.
                 * 
                 * This function processes the message received from the server,
                 * handling different types of commands and updating the client state accordingly.
                 * 
                 * @param message A vector of characters representing the message from the server.
                 */
                void handle_message(std::vector<char>& message);

                /**
                 * @brief Notifies the server that the client is currently playing.
                 * 
                 * This function sends a message to the server indicating that the client
                 * has started playing and is actively participating in the game.
                 */
                void send_server_playing();

                /**
                 * @brief Informs the server of a player jump action.
                 * 
                 * This function sends a message to the server whenever the client performs a jump
                 * action in the game.
                 */
                void send_server_jump();

                /**
                 * @brief Notifies the server that the game is being restarted.
                 * 
                 * This function sends a restart signal to the server to indicate that
                 * the client has restarted the game.
                 */
                void send_server_restart_game();

                /**
                 * @brief Creates a new player shoot action.
                 * 
                 * This function sends a message to the server when the player initiates
                 * a shooting action in the game.
                 */
                void create_new_player_shoot();

                /**
                 * @brief Handles the mouse click event.
                 * 
                 * This function processes mouse clicks, typically to interact with game objects
                 * or interface elements, such as buttons or menus.
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
                void add_level_status_screen();
                void restart_game(ecs::udp::Message&);
                void createEntityProjectile(unsigned int, float, float, int, int, int, int);
                // MESSAGE TO SERVER

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
                void init_player(unsigned int, float, float);
                void init_play_button();
                void init_game(ecs::udp::Message &);
        };
    }
#endif /* !CLIENT_HPP_ */
