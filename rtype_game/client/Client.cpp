/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"
#include <thread>
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
        send_server_client_leave();
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
        std::vector<std::tuple<std::pair<float, float>, int, int>> entities =
            Utils::parseUpdateEntities(message);

        while (!entities.empty()) {
            std::tuple<std::pair<float, float>, int, int> entity =
                entities.back();
            std::cout << "XX : " << std::get<0>(entity).first
                      << "yy : " << std::get<0>(entity).second << std::endl;
            createEntity(std::get<1>(entity), std::get<0>(entity).first,
                std::get<0>(entity).second,
                static_cast<SPRITES>(std::get<2>(entity)));
            entities.pop_back();
        }
    }

    void Client::setRoomAdress(int port)
    {
        std::string ip_port =
            Utils::check_adress(port, _udpClient->getServerIp());
        _udpClient->setDefaultAddress(ip_port);
    }

    void Client::changeDifficulty(DIFFICULTY difficulty)
    {
        _gameplay_factory->changeDifficulty(difficulty);
    }

    void Client::handle_message(std::vector<char> &message)
    {
        std::lock_guard<std::mutex> lock(roomListMutex);
        ecs::udp::Message mes;
        _message_compressor.deserialize(message, mes);
        Utils::checkAction(mes.action);
        rtype::RTYPE_ACTIONS action =
            static_cast<rtype::RTYPE_ACTIONS>(mes.action);
        _eventBus.emit(action, std::ref(mes));
    }

    void Client::restart_game()
    {
        _kill_system.killLevelStatus(_ecs);
        _kill_system.killTexts(_ecs);
        init_levels_sprites();
        if (_player_system.getIndexPlayer(_ecs._components_arrays) == -1)
            send_server_new_player();
    }

    void Client::launchMenu()
    {
        auto &windows = std::any_cast<ecs::SparseArray<Window> &>(
            _ecs._components_arrays.at(typeid(Window)));
        auto lawindow = windows[0].value().getRenderWindow().get();
        std::string playerName;

        try {
            InputScreen inputScreen(*lawindow);
            bool isInputScreen = true;
            inputScreen.run(isInputScreen, playerName);
        } catch (const std::exception &e) {
            std::cerr << "Erreur lors du chargement de l'écran d'entrée : "
                      << e.what() << "\n";
            return;
        }

        std::atomic<bool> runningNetworkThread{true};
        std::thread networkThread([&]() {
            while (runningNetworkThread) {
                auto messages = _udpClient->fetchAllMessages();
                for (auto &[clientAddress, message] : messages) {
                    try {
                        handle_message(message);
                    } catch (std::exception &e) {
                        std::cerr << std::endl << e.what() << std::endl;
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });

        std::atomic<bool> runningRequestListThread{true};
        std::thread requestRoomListThread([&]() {
            while (runningRequestListThread) {
                requestRoomList();
                std::this_thread::sleep_for(
                    std::chrono::seconds(1));
            }
        });

        try {
            Menu menu(*lawindow, playerName, *this);
            menu.run(_in_menu);
        } catch (const std::exception &e) {
            std::cerr << "Erreur lors du chargement du menu principal : "
                      << e.what() << "\n";
            return;
        }

        runningNetworkThread = false;
        if (networkThread.joinable()) {
            networkThread.join();
        }

        runningRequestListThread = false;
        if (requestRoomListThread.joinable()) {
            requestRoomListThread.join();
        }
    }

    void Client::start()
    {
        init_all();
        launchMenu();

        while (_running) {
            _timer->waitTPS();

            auto events = _event_window_system.fetchEvents();
            _sfml_handler->handleEvents(events);

            auto messages = _udpClient->fetchAllMessages();
            for (auto &[clientAddress, message] : messages) {
                try {
                    handle_message(message);
                } catch (std::exception &e) {
                    std::cerr << std::endl << e.what() << std::endl;
                }
            }

            _eventBus.emit(RTYPE_ACTIONS::UPDATE_POSITIONS);
            execute_animation();
            if (_inLevelStatus)
                levelStatusTime();
            _eventBus.emit(RTYPE_ACTIONS::MOVE_BACKGROUND);
            _eventBus.emit(RTYPE_ACTIONS::RENDER_WINDOW);
        }

        _eventBus.emit(RTYPE_ACTIONS::STOP_LISTEN_EVENT);
    }

} // namespace rtype
