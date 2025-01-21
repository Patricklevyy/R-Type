/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Room
*/

#include "Room.hpp"
#include <arpa/inet.h>
#include <cmath>
#include <cstring>
#include <random>
#include <sys/socket.h>

namespace rtype
{

    Room::Room(int port, const std::string &name)
        : _port(port), _name(name), _sockfd(-1)
    {
    }

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
        : _port(other._port), _name(std::move(other._name)),
          _sockfd(other._sockfd), _addr(other._addr)
    {
        other._sockfd = -1;
    }

    Room &Room::operator=(Room &&other) noexcept
    {
        if (this != &other) {
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
        if (_sockfd < 0) {
            std::cerr << "Socket creation failed for room " << _name
                      << std::endl;
            return false;
        }

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        _addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(_sockfd, (struct sockaddr *) &_addr, sizeof(_addr)) < 0) {
            std::cerr << "Bind failed for room " << _name << std::endl;
            close(_sockfd);
            return false;
        }

        std::cout << "Room " << _name << " is listening on port " << _port
                  << std::endl;
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
        ssize_t sent = sendto(_sockfd, message.c_str(), message.size(), 0,
            (struct sockaddr *) &_addr, sizeof(_addr));
        return sent >= 0;
    }

    size_t Room::getNextIndex()
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = index_ecs;
            index_ecs++;
        }
        return index;
    }

    void Room::startLevel(LEVELS level)
    {
        size_t index = getNextIndex();

        playingInLevel = true;
        _ecs.addComponents<Levels>(index, Levels(level));
        send_client_start_level();
    }

    void Room::handleCommand(
        const std::vector<char> &compressed_message, std::string clientAddr)
    {
        (void) clientAddr;
        ecs::udp::Message message;
        _message_compressor.deserialize(compressed_message, message);
        rtype::RTYPE_ACTIONS action =
            static_cast<rtype::RTYPE_ACTIONS>(message.action);
        _eventBus.emit(action, std::ref(message));
    }

    std::pair<float, float> Room::get_player_start_position(int nb_client)
    {
        switch (nb_client) {
            case 0: return std::pair<int, float>(200, 200);
            case 1: return std::pair<float, float>(300, 300);
            case 2: return std::pair<float, float>(400, 400);
            case 3: return std::pair<float, float>(500, 500);
            default: return std::pair<float, float>(0, 0);
        }
    }

    void Room::closeRoom()
    {
        if (_sockfd >= 0) {
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
        return std::string(ipStr) + ":"
            + std::to_string(ntohs(this->_addr.sin_port));
    }

} // namespace rtype
