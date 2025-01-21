/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

/**
 * @file Server.hpp
 * @brief Manages the overall server and its rooms.
 */

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "../shared/Includes.hpp"
    #include "../shared/Utils.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Manager.hpp"
    #include "../shared/Timer.hpp"
    #include "../shared/SecretKeyChecker.hpp"
    #include "Room.hpp"

    namespace poc_game
    {
        /**
         * @class Server
         * @brief Represents the game server and manages its rooms and clients.
         */
        class Server
        {
        public:
            /**
             * @brief Constructs the Server object.
             */
            Server();

            /**
             * @brief Destructor for Server.
             */
            ~Server();

            /**
             * @brief Starts the server and begins accepting connections.
             */
            void start();

        private:
            int _rooms_nb = 0;
            Timer _timer;
            bool _running = true;
            std::vector<Room> _rooms;
            int _currentPort;
            std::shared_ptr<ecs::udp::UDP_Manager> _udpManager;
            ecs::udp::MessageCompressor _compressor;
            std::unordered_map<unsigned int, std::function<void(const unsigned int, std::string &, std::string &)>> _commands;


            /**
             * @brief Initializes the command handlers for the server.
             */
            void initializeCommands();

            /**
             * @brief Starts a new game by creating a new room.
             * @param clientAddr The address of the client that requested the game start.
             * @param params The parameters containing additional information for the room setup.
             */
            void start_game(const std::string&, std::string &);

            /**
             * @brief Handles a command received from a client.
             * @param command The raw command data.
             * @param clientAddr The address of the client sending the command.
             */
            void handleCommand(const std::vector<char> &, std::string clientAddr);
        };
    }

#endif /* !SERVER_HPP_ */
