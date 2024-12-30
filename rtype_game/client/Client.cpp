/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"
#include "../../ecs/components/Direction.hpp"

namespace rtype
{
    Client::Client() : _sfml_handler(std::make_shared<SFMLHandler>(*this))
    {
        _udpClient = std::make_shared<ecs::udp::UDP_Client>();
        _timer = std::make_shared<Timer>();
        reset_level_lock();
    }

    Client::~Client()
    {
        _udpClient->stopReceiving();
    }

    size_t Client::getNextIndex()
    {
        size_t index;
        std::pair<bool, int> dead_entity = _ecs.getDeadEntityIndex();
        if (dead_entity.first) {
            index = dead_entity.second;
        } else {
            index = _index_ecs_client;
            _index_ecs_client++;
        }
        return index;
    }

    void Client::updateEntitiesFirstConnexion(const std::string &message)
    {
        std::vector<std::tuple<std::pair<float, float>, int, int>> entities = Command_checker::parseUpdateEntities(message);

        while (!entities.empty()) {
            std::tuple<std::pair<float, float>, int, int> entity = entities.back();
            std::cout << "XX : " << std::get<0>(entity).first << "yy : " << std::get<0>(entity).second << std::endl;
            createEntity(std::get<1>(entity), std::get<0>(entity).first, std::get<0>(entity).second, static_cast<SPRITES>(std::get<2>(entity)));
            entities.pop_back();
        }
    }

    void Client::setRoomAdress(int port)
    {
        std::string ip_port = Command_checker::check_adress(port, _udpClient->getServerIp());
        _udpClient->setDefaultAddress(ip_port);
    }

    void Client::handle_message(std::vector<char> &message)
    {
        ecs::udp::Message mes;
        _message_compressor.deserialize(message, mes);
        Utils::checkAction(mes.action);
        std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << std::endl;
        rtype::RTYPE_ACTIONS action = static_cast<rtype::RTYPE_ACTIONS>(mes.action);
        _eventBus.emit(action, std::ref(mes));
    }

    void Client::restart_game()
    {
        _kill_system.killTempDisplay(_ecs);
        init_levels_sprites();
        if (_player_system.getIndexPlayer(_ecs._components_arrays) == -1)
            send_server_new_player();
    }

    void Client::send_server_new_player()
    {
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 0;
        mess.action = RTYPE_ACTIONS::CREATE_PLAYER;
        mess.secret_key = _udpClient->getSecretKey();
        _message_compressor.serialize(mess, buffer);

        std::cout << "je send" << std::endl;
        if (_udpClient->sendMessageToDefault(buffer)) {
            std::cout << "Message sent: " << std::endl;
        } else {
            std::cout << "failed " << std::endl;
        }
    }

    void Client::start()
    {
        init_all();

        std::queue<sf::Event> events;
        while (_running) {
            _timer->waitTPS();
            events = _event_window_system.fetchEvents();
            _sfml_handler->handleEvents(events);
            auto messages = _udpClient->fetchAllMessages();
            for (auto &[clientAddress, message] : messages) {
                try {
                    handle_message(message);
                } catch (std::exception &e) {
                    std::cerr << std::endl
                              << e.what() << std::endl;
                }
            }
            _eventBus.emit(RTYPE_ACTIONS::UPDATE_POSITIONS);
            _eventBus.emit(RTYPE_ACTIONS::MOVE_BACKGROUND);
            _eventBus.emit(RTYPE_ACTIONS::RENDER_WINDOW);
        }
        _eventBus.emit(RTYPE_ACTIONS::STOP_LISTEN_EVENT);
    }
}
