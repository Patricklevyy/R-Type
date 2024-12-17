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
#include <sys/socket.h>

std::unordered_map<std::string, std::string> parseParams(const std::string &params)
{
    std::unordered_map<std::string, std::string> parsed;
    std::stringstream ss(params);
    std::string item;

    while (std::getline(ss, item, ';')) {
        size_t eqPos = item.find('=');
        if (eqPos != std::string::npos) {
            std::string key = item.substr(0, eqPos);
            std::string value = item.substr(eqPos + 1);
            parsed[key] = value;
        }
    }
    return parsed;
}

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
        : _port(other._port), _name(std::move(other._name)), _sockfd(other._sockfd), _addr(other._addr)
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
            std::cerr << "Socket creation failed for room " << _name << std::endl;
            return false;
        }

        _addr.sin_family = AF_INET;
        _addr.sin_port = htons(_port);
        _addr.sin_addr.s_addr = INADDR_ANY;

        if (bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) < 0) {
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

    void Room::init_event_bus()
    {
        // SUBSCRIBE POSITION SYSTEM
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::UPDATE_POSITION, [this](const std::vector<std::any> &args) {
            (void)args;
            _positon_system.updatePositions(_ecs._components_arrays, _timer.getTps(), _window_width, _window_height);
        });
        _eventBus.subscribe(RTYPE_ACTIONS::UPDATE_DIRECTION, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();
                std::tuple<ecs::direction, ecs::direction, size_t> _x_y_index = Utils::extractPlayerPosIndex(message.params, message.id);

                _direction_system.updatePlayerDirection(_ecs._components_arrays, std::get<0>(_x_y_index), std::get<1>(_x_y_index), std::get<2>(_x_y_index));
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::PLAYER_SHOOT, [this](const std::vector<std::any> &args) {
            try {
                ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

                createProjectile(message);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_OFF_SCREEN, [this](const std::vector<std::any> &args) {
            try {
                (void)args;

                std::list<size_t> dead_entites_id = _boundaries_system.checkAndKillEntities(_ecs, _window_width, _window_height);
                if (!dead_entites_id.empty())
                    send_client_dead_entities(dead_entites_id);
            } catch (const std::bad_any_cast &e) {
                std::cerr << "Error during event handling: dans" << e.what() << std::endl;
            }
        });
        // _eventBus.subscribe(RTYPE_ACTIONS::MOVE_MONSTERS, [this](const std::vector<std::any>& args) {
        //     (void)args;
        //     _monster_movement_system.moveMonsters(_ecs, _timer.getTps());
        // });
        _eventBus.subscribe(RTYPE_ACTIONS::CREATE_MONSTER, [this](const std::vector<std::any> &args) {
            (void)args;
            ecs::udp::Message message = std::any_cast<std::reference_wrapper<ecs::udp::Message>>(args[0]).get();

            createMonster(message);
        });
    }

    void Room::send_client_dead_entities(std::list<size_t> dead_entities_id)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::KILL_PROJECTILES;
        responseMessage.id = 0;

        std::string ids;
        for (const auto &id : dead_entities_id) {
            if (!ids.empty()) {
                ids += ";";
            }
            ids += std::to_string(id);
        }

        responseMessage.params = ids;
        std::cout << "DEAD ENTITIES : " << responseMessage.params << std::endl;

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::send_client_new_projectile(size_t index_ecs_server, float x, float y)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::CREATE_PROJECTILE;
        responseMessage.id = index_ecs_server;
        std::cout << "JE SHOTT" << "x=" + std::to_string(x) + ";y=" + std::to_string(y) + ";type=" + std::to_string(SPRITES::PLAYER_SIMPLE_MISSILE) << std::endl;
        responseMessage.params = "x=" + std::to_string(x) + ";y=" + std::to_string(y) + ";type=" + std::to_string(SPRITES::PLAYER_SIMPLE_MISSILE);

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::createProjectile(ecs::udp::Message &message)
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = index_ecs;
            index_ecs++;
        }
        std::pair<std::pair<float, float>, std::pair<int, int>> pos_dir = Utils::extractProjectilePosAndDir(message.params);
        ecs::Direction direction(static_cast<ecs::direction>(pos_dir.second.first), static_cast<ecs::direction>(pos_dir.second.second));
        ecs::Position position(pos_dir.first.first, pos_dir.first.second);
        ecs::Velocity velocity;
        Health health;
        Projectiles projectile;
        SpriteId spriteId(SPRITES::PLAYER_SIMPLE_MISSILE);

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Projectiles>(index, projectile);
        _ecs.addComponents<SpriteId>(index, spriteId);
        send_client_new_projectile(index, pos_dir.first.first, pos_dir.first.second);
    }

    void Room::createMonster(ecs::udp::Message &message)
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = index_ecs;
            index_ecs++;
        }
        std::unordered_map<std::string, std::string> res = MessageChecker::parseResponse(message.params);
        if (res.find("x") == res.end() || res.find("y") == res.end()) {
            std::cerr << "Error: Missing x or y in message parameters" << std::endl;
            return;
        }
        int x = std::stoi(res["x"]);
        int y = std::stoi(res["y"]);
        ecs::Position position(x, y);
        ecs::Velocity velocity;
        Health health;
        health._health = 200;
        Monster monster;

        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<Monster>(index, monster);

        send_client_new_monster(index, x, y, SPRITES::MONSTER);
    }

    void Room::handleCommand(const std::vector<char> &compressed_message, std::string clientAddr)
    {
        (void)clientAddr; // POUR L'INSTANT ON NE L'UTILISE PAS, PEUT ETRE PLUS TARD POUR LES ROLLBACK ETC
        ecs::udp::Message message;
        _message_compressor.deserialize(compressed_message, message);
        std::cout << "new message in the ROOOM :" << message.id << "action : " << message.action << ", " << message.params << std::endl;
        rtype::RTYPE_ACTIONS action = static_cast<rtype::RTYPE_ACTIONS>(message.action);
        _eventBus.emit(action, std::ref(message));
    }

    void Room::init_ecs_server_registry()
    {
        _ecs.addRegistry<Health>();
        _ecs.addRegistry<Projectiles>();
        _ecs.addRegistry<SpriteId>();
        _ecs.addRegistry<Monster>();
    }

    void Room::gameThreadFunction(int port, std::string lastClientAddr, std::string clientName, std::string window_width, std::string window_height)
    {
        _window_width = std::stoi(window_width);
        _window_height = std::stoi(window_height);
        _port = port;
        _udp_server = std::make_shared<ecs::udp::UDP_Server>();

        if (!_udp_server->initialize("rtype_game/config/udp_config.conf", port)) {
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
            // _eventBus.emit(RTYPE_ACTIONS::MOVE_MONSTERS);
            _eventBus.emit(RTYPE_ACTIONS::CHECK_OFF_SCREEN);
            _ecs.displayPlayableEntityComponents();
            auto messages = _udp_server->fetchAllMessages();
            if (messages.size() != 0) {
                for (const auto &[clientAddress, message] : messages) {
                    handleCommand(message, clientAddress);
                }
            }
            sendUpdate();
        }
        _udp_server->stopReceiving();
    }

    void Room::start(int port, std::string lastclientAddr, std::string clientName, std::string window_width, std::string window_height)
    {
        std::cout << "j'inite et je creer les threads" << std::endl;
        _gameThread = std::thread(&Room::gameThreadFunction, this, port, lastclientAddr, clientName, window_width, window_height);
        _gameThread.detach();
    }

    std::pair<float, float> Room::get_player_start_position(int nb_client)
    {
        switch (nb_client) {
        case 0:
            return std::pair<int, float>(200, 200);
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

        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(_ecs._components_arrays[typeid(ecs::Position)]);
        auto &healths = std::any_cast<ecs::SparseArray<Health> &>(_ecs._components_arrays[typeid(Health)]);

        for (size_t i = 0; i < positions.size(); ++i) {
            if (positions[i].has_value() && healths[i].has_value()) {

                updateMessage += std::to_string(i) +
                "," + std::to_string(static_cast<int>(round(positions[i].value()._pos_x))) +
                "," + std::to_string(static_cast<int>(round(positions[i].value()._pos_y))) +
                "," + std::to_string(healths[i].value()._health) + ";";
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
        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    size_t Room::create_player(std::pair<float, float> positions, std::string clientName)
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = index_ecs;
            index_ecs++;
        }

        ecs::Direction direction;
        ecs::Playable playable(clientName);
        ecs::Position position(positions.first, positions.second);
        ecs::Velocity velocity;
        Health health;
        SpriteId spriteId(SPRITES::MY_PLAYER_SHIP);

        _ecs.addComponents<ecs::Direction>(index, direction);
        _ecs.addComponents<ecs::Playable>(index, playable);
        _ecs.addComponents<ecs::Velocity>(index, velocity);
        _ecs.addComponents<ecs::Position>(index, position);
        _ecs.addComponents<Health>(index, health);
        _ecs.addComponents<SpriteId>(index, spriteId);

        return index;
    }

    void Room::send_client_new_monster(size_t index_ecs_server, float x, float y, int type)
    {
        std::vector<char> response;
        ecs::udp::Message responseMessage;
        responseMessage.action = RTYPE_ACTIONS::CREATE_MONSTER;
        responseMessage.id = index_ecs_server;
        responseMessage.params = "x=" + std::to_string(x) + ";y=" + std::to_string(y) + ";type=" + std::to_string(type);

        _message_compressor.serialize(responseMessage, response);

        for (const auto &clientAddr : _clientAddresses) {
            _udp_server->sendMessage(response, clientAddr);
        }
    }

    void Room::createClient(std::string lastclientAdr, std::string clientName)
    {
        std::cout << "Client created in room [" << _name << "] with addr: " << lastclientAdr << std::endl;

        std::string roomAddress = getAddress();

        std::pair<float, float> position = get_player_start_position(getNbClient());

        std::vector<char> send_message;
        ecs::udp::Message mes;
        mes.action = RTYPE_ACTIONS::CREATE_CLIENT;
        mes.params = std::to_string(static_cast<int>(position.first)) + ";" + std::to_string(static_cast<int>(position.second)) + ";" + std::to_string(_port) + ":" + sendExistingEntities(lastclientAdr);
        ;

        std::cout << "CREATE CLINET : " << mes.params << std::endl;
        mes.id = create_player(position, clientName);
        _message_compressor.serialize(mes, send_message);
        _clientAddresses.push_back(lastclientAdr);
        std::cout << lastclientAdr << std::endl;
        if (_udp_server->sendMessage(send_message, lastclientAdr)) {

            std::cout << "Message sent: " << mes.params << mes.action << std::endl;
        } else {
            std::cerr << "Failed to send message." << std::endl;
        }
        mes.action = RTYPE_ACTIONS::CREATE_TEAMMATE;
        size_t port_pos = mes.params.find(";port=");
        if (port_pos != std::string::npos) {
            mes.params.erase(port_pos);
        }
        _message_compressor.serialize(mes, send_message);
        for (const auto &clientAddr : _clientAddresses) {
            if (clientAddr != lastclientAdr)
                _udp_server->sendMessage(send_message, clientAddr);
        }
        setNbClient(getNbClient() + 1);
        index_ecs++;
    }

    std::string Room::sendExistingEntities(const std::string &clientAddress)
    {
        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(_ecs._components_arrays[typeid(ecs::Position)]);
        auto &sprite = std::any_cast<ecs::SparseArray<SpriteId> &>(_ecs._components_arrays[typeid(SpriteId)]);

        std::string updateMessage = "";

        for (size_t i = 0; i < positions.size(); ++i) {
            if (positions[i].has_value() && sprite[i].has_value()) {
                int spriteId = sprite[i].value()._sprite;
                if (spriteId == 1)
                    spriteId = 4;
                updateMessage += std::to_string(positions[i].value()._pos_x) +
                "," + std::to_string(positions[i].value()._pos_y) +
                "," + std::to_string(i) +
                "," + std::to_string(spriteId) + ";";
            }
        }

        return updateMessage;
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
        return std::string(ipStr) + ":" + std::to_string(ntohs(this->_addr.sin_port));
    }

}
