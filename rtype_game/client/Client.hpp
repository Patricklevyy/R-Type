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
    #include "../shared/Room.hpp"
    #include "Command_checker.hpp"
    #include "../shared/Utils.hpp"
    #include "./Menu.hpp"

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

    namespace rtype
    {
        class SFMLHandler;
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

                void change_player_direction(ecs::direction, ecs::direction);

                void send_server_create_room();

                void send_server_join_room();

                void set_window_filter(FILTER_MODE);

                void create_new_player_shoot();

                void handleMouseClick();

                bool _in_menu = true;
                bool _running = true;
                EventBus _eventBus;

            protected:
            private:
                int _window_width;
                int _window_height;
                std::string _name;
                std::map<int, int> ecs_server_to_client;
                std::map<int, int> ecs_client_to_server;
                std::map<LEVELS, bool> _levels_wins;
                ecs::ECS _ecs;
                std::queue<sf::Event> _events;
                size_t _index_ecs_client = 0;
                std::vector<Room> _rooms;
                std::vector<std::pair<std::string, int>> _roomsList;
                

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
                size_t getNextIndex();
                void add_level_status_screen(bool, ecs::udp::Message &);
                void restart_game();
                void send_server_new_player();
                void createEntityProjectile(unsigned int, float, float, int, int, int, int);
                void reset_level_lock();
                void put_level_lock(LEVELS, int, int);
                // MESSAGE TO SERVER

                /**
                 * @brief Sends a message to the server indicating a new shoot action.
                 */
                void send_server_new_shoot();

                void send_server_start_game(LEVELS);

                /**
                 * @brief Sends a message to the server to ask the list of all the rooms.
                 */
                void requestRoomList();

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
                 * @brief Initializes the game menu.
                 */
                void init_menu();

                /**
                 * @brief Initializes the ECS client registry.
                 */
                void init_ecs_client_registry();

                /**
                 * @brief Initializes the event bus subscription.
                 */
                void init_subscribe_event_bus();
                void init_levels_sprites();
                std::vector<std::pair<std::string, int>> parseRoomList(const std::string &);
        };
    }
#endif /* !CLIENT_HPP_ */
