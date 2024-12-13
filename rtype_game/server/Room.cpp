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
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [this](const std::vector<std::any>& args) {
            _positon_system.updatePositions(_ecs._components_arrays, _timer.getTps());
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_DIRECTION, [this](const std::vector<std::any>& args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();
                std::tuple<ecs::direction, ecs::direction, size_t> _x_y_index = Utils::extractPlayerPosIndex(message.params, message.id);

                _direction_system.updatePlayerDirection(_ecs._components_arrays, std::get<0>(_x_y_index), std::get<1>(_x_y_index), std::get<2>(_x_y_index));
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
    }

    void Room::handleCommand(const std::vector<char> &compressed_message, std::string clientAddr)
    {
        ecs::udp::Message message;
        _message_compressor.deserialize(compressed_message, message);
        std::cout << "new message in the ROOOM :" << message.id << "action : " << message.action << ", " << message.params << std::endl;
        rtype::RTYPE_ACTIONS action = static_cast<rtype::RTYPE_ACTIONS>(message.action);
        _eventBus.emit(action, std::ref(message));
    }

    void Room::init_ecs_server_registry()
    {
        _ecs.addRegistry<Health>();
        // INIT LES COMPONENT DU SERVER QUI SONT PAS COMMUN AVEC LE CLIENT
    }

    void Room::gameThreadFunction(int port, std::string lastClientAddr, std::string clientName)
    {
        _port = port;
        _udp_server = std::make_shared<ecs::udp::UDP_Server>();

        if (!_udp_server->initialize("rtype_game/config/udp_config.conf", port))
        {
            std::cerr << "Failed to initialize socket for room " << _name << std::endl;
            return;
        }
        _ecs.init_basic_registry();
        init_ecs_server_registry();
        _udp_server->startReceiving();
        _timer.init("rtype_game/config/server_config.conf", true);
        _game_running = true;
        createClient(lastClientAddr, clientName);
        std::cout << "je suis dans le game thread" << std::endl;
        init_event_bus();

        while (_game_running) {
            _timer.waitTPS();
            _eventBus.emit(RTYPE_ACTIONS::UPDATE_POSITION);
            _ecs.displayPlayableEntityComponents();
            auto messages = _udp_server->fetchAllMessages();
            if (messages.size() != 0) {
                for (const auto &[clientAddress, message] : messages)
                {
                    handleCommand(message, clientAddress);
                }
            }
            sendUpdate();
        }
        _udp_server->stopReceiving();
    }

    void Room::start(int port, std::string lastclientAddr, std::string clientName)
    {
        std::cout << "j'inite et je creer les threads" << std::endl;
        _gameThread = std::thread(&Room::gameThreadFunction, this, port, lastclientAddr, clientName);
        _gameThread.detach();
    }

    std::pair<float, float> Room::get_player_start_position(int nb_client)
    {
        switch (nb_client)
        {
        case 0:
            return std::pair<float, float>(200, 200);
        case 1:
            return std::pair<float, float>(300, 300);
        case 2:
            return std::pair<float, float>(400, 400);
        case 3:
            return std::pair<float, float>(500, 500);
        default:
            // IMPOSSIBLE CASE
            return std::pair<float, float>(0, 0);
        }
    }

    void Room::sendUpdate()
    {
        std::string updateMessage = "";

        auto& positions = std::any_cast<ecs::SparseArray<ecs::Position>&>(_ecs._components_arrays[typeid(ecs::Position)]);
        auto& healths = std::any_cast<ecs::SparseArray<Health>&>(_ecs._components_arrays[typeid(Health)]);
        auto& playables = std::any_cast<ecs::SparseArray<ecs::Playable>&>(_ecs._components_arrays[typeid(ecs::Playable)]);

        for (size_t i = 0; i < positions.size(); ++i) {
            if (positions[i].has_value() && healths[i].has_value()) {
                const auto& position = positions[i].value();
                const auto& health = healths[i].value();

                updateMessage += ",id=" + std::to_string(i) +
                                 ",x=" + std::to_string(positions[i].value()._pos_x) +
                                 ",y=" + std::to_string(positions[i].value()._pos_y) +
                                 ",health=" + std::to_string(healths[i].value()._health) + ";";
                }
        }

        if (!updateMessage.empty() && updateMessage.back() == ';') {
            updateMessage.pop_back();
        }

        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::UPDATE_POSITION;
        responseMessage.id = 0;
        responseMessage.params = updateMessage;

        _message_compressor.serialize(responseMessage, response);
        for (const auto& clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }


    void Room::create_player(size_t index, std::pair<float, float> positions, std::string clientName)
    {
        ecs::Direction direction;
        ecs::Playable playable(clientName);
        ecs::Position position(positions.first, positions.second);
        ecs::Velocity velocity;
        Health health;

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Playable>(index, playable);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
    }

    void Room::createClient(std::string lastclientAdr, std::string clientName)
    {
        std::cout << "Client created in room [" << _name << "] with addr: " << lastclientAdr << std::endl;

        std::string roomAddress = getAddress();

        ecs::udp::Message mes;

        mes.id = index_ecs;
        mes.action = RTYPE_ACTIONS::CREATE_CLIENT;
        std::pair<float, float> position = get_player_start_position(getNbClient());
        mes.params = "x=" + std::to_string(position.first) + ";y=" + std::to_string(position.second) + ";port=" + std::to_string(_port);
        std::vector<char> send_message;

        create_player(index_ecs, position, clientName);

        _message_compressor.serialize(mes, send_message);
        _clientAddresses.push_back(lastclientAdr);
        std::cout << lastclientAdr << std::endl;
        if (_udp_server->sendMessage(send_message, lastclientAdr)) {

            std::cout << "Message sent: "  << mes.params << mes.action << std::endl;
        } else {
            std::cerr << "Failed to send message." << std::endl;
        }
        mes.action = RTYPE_ACTIONS::CREATE_TEAMMATE;
        size_t port_pos = mes.params.find(";port=");
        if (port_pos != std::string::npos) {
            mes.params.erase(port_pos);
        }
        _message_compressor.serialize(mes, send_message);
        for (const auto& clientAddr : _clientAddresses) {
            if (clientAddr != lastclientAdr)
                _udp_server->sendMessage(send_message, clientAddr);
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
