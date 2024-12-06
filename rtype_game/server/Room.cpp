/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

#include "Room.hpp"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>

namespace rtype
{

    Room::Room(int port, const std::string &name)
        : _port(port), _name(name), _sockfd(-1) {}

    Room::~Room()
    {
        if (_sockfd >= 0) {
            close(_sockfd);
        }
        if (_listenThread.joinable()) {
            _listenThread.join();
        }
        if (_gameThread.joinable()) {
            _gameThread.join();
        }
    }

    Room::Room(Room &&other) noexcept
        : _port(other._port), _name(std::move(other._name)), _sockfd(other._sockfd), _addr(other._addr), _listenThread(std::move(other._listenThread))
    {
        other._sockfd = -1;
    }

    Room &Room::operator=(Room &&other) noexcept
    {
        if (this != &other)
        {
            _port = other._port;
            _name = std::move(other._name);
            _sockfd = other._sockfd;
            _addr = other._addr;
            _listenThread = std::move(other._listenThread);

            other._sockfd = -1;
        }
        return *this;
    }

    bool Room::initializeSocket()
    {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            std::cerr << "Socket creation failed for room " << _name << std::endl;
            return false;
        }

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        _addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0)
        {
            std::cerr << "Bind failed for room " << _name << std::endl;
            close(_sockfd);
            return false;
        }

        std::cout << "Room " << _name << " is listening on port " << _port << std::endl;
        return true;
    }

    unsigned int Room::getNbClient() const
    {
        return _nb_client;
    }

    void Room::setNbClient(unsigned int nb_client)
    {
        _nb_client = nb_client;
    }

    void Room::listenForMessages()
    {
        // char buffer[1024];
        // sockaddr_in senderAddr;
        // socklen_t senderLen = sizeof(senderAddr);

        // while (true)
        // {
        //     ssize_t received = recvfrom(_sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&senderAddr, &senderLen);
        //     if (received > 0)
        //     {
        //         std::string message(buffer, received);
        //         std::cout << "Received message in room thread " << _name << ": " << message << std::endl;

        //         if (message == "CREATE")
        //         {
        //             char ipStr[INET_ADDRSTRLEN];
        //             inet_ntop(AF_INET, &(senderAddr.sin_addr), ipStr, INET_ADDRSTRLEN);
        //             int clientPort = ntohs(senderAddr.sin_port);

        //             std::string clientAddress = std::string(ipStr) + ":" + std::to_string(clientPort);

        //             std::string roomAddress = "127.0.0.1:" + std::to_string(_port); // L'adresse et le port de la room

        //             std::string response = "The room address is: " + roomAddress;

        //             // if (!_udpServer.sendMessage(response, clientAddress))
        //             // {
        //             //     std::cerr << "Failed to send room address to client." << std::endl;
        //             // }
        //             // else
        //             // {
        //             //     std::cout << "Sent room address to client: " << roomAddress << std::endl;
        //             // }
        //         }
        //     }
        // }
    }

    bool Room::sendMessage(const std::string &message)
    {
        ssize_t sent = sendto(_sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&_addr, sizeof(_addr));
        return sent >= 0;
    }

    void Room::gameThreadFunction() {
        _ecs.init_basic_registry();
        std::cout << "je suis dans le game thread" << std::endl;
        ecs::PositionSystem pos_system;

        ecs::Position pos;
        pos.pos_x = 47;
        pos.pos_y = 100;

        ecs::Velocity vel;
        vel.velocity = 12.5;

        ecs::Direction dir;
        dir._x = ecs::direction::RIGHT;

        ecs::Playable player;

        try {
            _ecs.addComponents<ecs::Position>(2, pos);
            _ecs.addComponents<ecs::Velocity>(2, vel);
            _ecs.addComponents<ecs::Direction>(2, dir);
            _ecs.addComponents<ecs::Playable>(2, player);
        } catch (std::exception &e) {
            std::cerr << std::endl << e.what() << std::endl;
        }
        _ecs.displayPlayableEntityComponents();
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [](const std::vector<std::any>& args) {
            try {
                auto& ps = std::any_cast<std::reference_wrapper<ecs::PositionSystem>>(args[0]).get();
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[1]).get();

                ps.updatePositions(components);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.emit(
            rtype::RTYPE_ACTIONS::UPDATE_POSITION,
            std::ref(pos_system),
            std::ref(_ecs._components_arrays)
        );
        _ecs.displayPlayableEntityComponents();
    }

    void Room::start(int port)
    {
        if (!_udpServer.initialize("rtype_game/config/udp_config.conf", port))
        {
            std::cerr << "Failed to initialize socket for room " << _name << std::endl;
            return;
        }
        std::cout << "j'inite et je creer les threads" << std::endl;
        _listenThread = std::thread(&Room::listenForMessages, this);
        _listenThread.detach(); // Laisser le thread détaché pour tourner en arrière-plan
        _gameThread = std::thread(&Room::gameThreadFunction, this);
        _gameThread.join();

    }

    void Room::createClient(std::string lastclientAdr)
    {

        std::cout << "Client created in room [" << _name << "] with addr: " << lastclientAdr << std::endl;

        std::string roomAddress = getAddress();

        std::string message = "Welcome to the room, client! The room address is: " + roomAddress;

        // _udpServer.sendMessage(message, lastclientAdr);
        setNbClient(getNbClient() + 1);
    }

    void Room::closeRoom()
    {
        if (_sockfd >= 0)
        {
            close(_sockfd);
            _sockfd = -1;
        }
    }

    std::string Room::getName() const
    {
        return _name;
    }

    std::string Room::getAddress() const
    {
        char ipStr[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(this->_addr.sin_addr), ipStr, INET_ADDRSTRLEN);
        return std::string(ipStr) + ":" + std::to_string(ntohs(this->_addr.sin_port));
    }

}
