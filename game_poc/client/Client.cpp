/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"
#include "../../ecs/components/Direction.hpp"

namespace poc_game
{
    Client::Client() : _sfml_handler(std::make_shared<SFMLHandler>(*this))
    {
        _udpClient = std::make_shared<ecs::udp::UDP_Client>();
        _timer = std::make_shared<Timer>();
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

    void Client::setRoomAdress(int port)
    {
        std::string ip_port = Utils::check_adress(port, _udpClient->getServerIp());
        _udpClient->setDefaultAddress(ip_port);
    }

    void Client::handle_message(std::vector<char> &message)
    {
        ecs::udp::Message mes;
        _message_compressor.deserialize(message, mes);
        Utils::checkAction(mes.action);
        // std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << std::endl;
        POC_GAME_ACTIONS action = static_cast<POC_GAME_ACTIONS>(mes.action);
        _eventBus.emit(action, std::ref(mes));
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
            _eventBus.emit(POC_GAME_ACTIONS::UPDATE_POSITIONS);
            // _eventBus.emit(RTYPE_ACTIONS::MOVE_BACKGROUND);
            _eventBus.emit(POC_GAME_ACTIONS::RENDER_WINDOW);
        }
        _eventBus.emit(POC_GAME_ACTIONS::STOP_LISTEN_EVENT);
    }
}
