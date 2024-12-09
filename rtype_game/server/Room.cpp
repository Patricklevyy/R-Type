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
        if (_gameThread.joinable()) {
            _gameThread.join();
        }
    }

    Room::Room(Room &&other) noexcept
        : _port(other._port), _name(std::move(other._name)), _sockfd(other._sockfd), _addr(other._addr)
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

    bool Room::sendMessage(const std::string &message)
    {
        ssize_t sent = sendto(_sockfd, message.c_str(), message.size(), 0, (struct sockaddr *)&_addr, sizeof(_addr));
        return sent >= 0;
    }

    void Room::init_event_bus() {
        // SUBSCRIBE POSITION SYSTEM
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [](const std::vector<std::any>& args) {
            try {
                auto& ps = std::any_cast<std::reference_wrapper<ecs::PositionSystem>>(args[0]).get();
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[1]).get();

                ps.updatePositions(components);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
    }

    void Room::handleCommand(const std::vector<char> &compressed_message, std::string clientAddr)
    {
        ecs::udp::Message message;
        _message_compressor.deserialize(compressed_message, message);
        std::cout << "new message in the ROOOM :" << message.action << ", " << message.params << std::endl;
    }

    void Room::init_ecs_server_registry()
    {
        // INIT LES COMPONENT DU SERVER QUI SONT PAS COMMUN AVEC LE CLIENT
    }

    void Room::gameThreadFunction(int port, std::string lastClientAddr)
    {
        _port = port;
        Timer timer;
        _udp_server = std::make_shared<ecs::udp::UDP_Server>();

        if (!_udp_server->initialize("rtype_game/config/udp_config.conf", port))
        {
            std::cerr << "Failed to initialize socket for room " << _name << std::endl;
            return;
        }
        createClient(lastClientAddr);
        _udp_server->startReceiving();
        timer.init("rtype_game/config/server_config.conf", true);
        _game_running = true;
        _ecs.init_basic_registry();
        init_ecs_server_registry();
        std::cout << "je suis dans le game thread" << std::endl;
        init_event_bus();
        while (_game_running) {
            timer.waitTPS();
            auto messages = _udp_server->fetchAllMessages();
            if (messages.size() != 0) {
                for (const auto &[clientAddress, message] : messages)
                {
                    handleCommand(message, clientAddress);
                }
            }
        }
        _udp_server->stopReceiving();
    }

    void Room::start(int port, std::string lastclientAddr)
    {
        std::cout << "j'inite et je creer les threads" << std::endl;
        _gameThread = std::thread(&Room::gameThreadFunction, this, port, lastclientAddr);
        _gameThread.detach();
    }

    void Room::createClient(std::string lastclientAdr)
    {
        std::cout << "Client created in room [" << _name << "] with addr: " << lastclientAdr << std::endl;

        std::string roomAddress = getAddress();

        ecs::udp::Message mes;

        mes.id = index_ecs;
        mes.action = RTYPE_ACTIONS::CREATE_CLIENT;
        mes.params = "x=200;y=200;port=" + std::to_string(_port);

        std::vector<char> send_message;

        _message_compressor.serialize(mes, send_message);

        std::cout << lastclientAdr << std::endl;
        if (_udp_server->sendMessage(send_message, lastclientAdr)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cerr << "Failed to send message." << std::endl;
        }
        setNbClient(getNbClient() + 1);
        index_ecs++;
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
