/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#ifndef SERVER_HPP_
    #define SERVER_HPP_

    #include "Room.hpp"
    #include "../shared/Includes.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"
    #include "../../ecs/udp/UDP_Manager.hpp"
    #include "../shared/Timer.hpp"

    namespace rtype
    {
        class Server
        {
        public:
            Server();
            ~Server();

            void start();

            bool isRunning() const;
            void setRunning(bool);

        private:
            Timer _timer;
            bool _running;
            std::vector<Room> _rooms;
            int _currentPort;
            ecs::udp::UDP_Manager _udpManager;
            ecs::udp::MessageCompressor _compressor;
            MessageChecker _mes_checker;
            std::unordered_map<unsigned int, std::function<void(const unsigned int, std::string &, std::string &, std::string &)>> _commands;

            void initializeCommands();
            void handleCommand(const std::vector<char> &, std::string clientAddr);

            void checkCreateRoomArgs(std::map<std::string, std::string>);
            void checkJoinRoomArgs(std::map<std::string, std::string>);

            //  COMMANDS

            void createRoom(const unsigned int, std::string &, std::string &, std::string &);
            void joinRoom(const unsigned int, std::string &, std::string &, std::string &);
        };
    }

#endif /* !SERVER_HPP_ */
