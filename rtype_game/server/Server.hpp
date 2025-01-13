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

    #include "Room.hpp"
    #include "../shared/Includes.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Manager.hpp"
    #include "../shared/Timer.hpp"
    #include "../shared/SecretKeyChecker.hpp"

    namespace rtype
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
            Timer _timer;
            bool _running = true;
            std::vector<std::shared_ptr<Room>> _rooms;
            int _currentPort;
            std::shared_ptr<ecs::udp::UDP_Manager> _udpManager;
            ecs::udp::MessageCompressor _compressor;
            std::unordered_map<unsigned int, std::function<void(const unsigned int, std::string &, std::string &)>> _commands;


            /**
             * @brief Initializes the command handlers for the server.
             */
            void initializeCommands();

            /**
             * @brief Handles a command received from a client.
             * @param command The raw command data.
             * @param clientAddr The address of the client sending the command.
             */
            void handleCommand(const std::vector<char> &, std::string clientAddr);

            /**
             * @brief Validates arguments for the "Create Room" command.
             * @param args A map of arguments provided by the client.
             */
            void checkCreateRoomArgs(std::map<std::string, std::string>);

            /**
             * @brief Validates arguments for the "Join Room" command.
             * @param args A map of arguments provided by the client.
             */
            void checkJoinRoomArgs(std::map<std::string, std::string>);

            //  COMMANDS

            /**
            * @brief Handles the creation of a new room.
            * @param id The command ID.
            * @param input The raw input string from the client.
            * @param output The response string to be sent back to the client.
            */
            void createRoom(const unsigned int, std::string &);

            /**
            * @brief Handles a client's request to join an existing room.
            * @param id The command ID.
            * @param input The raw input string from the client.
            * @param output The response string to be sent back to the client.
            */
            void joinRoom(const unsigned int, std::string &, std::string &);

            /**
            * @brief Retrieves information about all active rooms and sends it to the client.
            * @param output The response string containing the room information.
            */
            void getAllRooms(std::string &);
        };
    }

#endif /* !SERVER_HPP_ */
