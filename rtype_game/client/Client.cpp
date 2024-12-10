/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#include "Client.hpp"
#include "../../ecs/components/Direction.hpp"
#include "../../ecs/components/Window.hpp"
#include "../../ecs/components/Background.hpp"
#include "../../ecs/system/EventWindow.hpp"

namespace rtype
{
    Client::Client()
    {
        _udpClient = std::make_shared<ecs::udp::UDP_Client>();
        _timer = std::make_shared<Timer>();
    }

    Client::~Client()
    {
        _udpClient->stopReceiving();
    }

    void Client::init_ecs_client_registry()
    {
        _ecs.addRegistry<Window>();
    }

    void Client::init_subscribe_event_bus()
    {
        _eventBus.subscribe(RTYPE_ACTIONS::CHECK_EVENT_WINDOW, [](const std::vector<std::any>& args) {
            try {
                auto& event_system = std::any_cast<std::reference_wrapper<EventWindow>>(args[0]).get();
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[1]).get();
                auto& queue = std::any_cast<std::reference_wrapper<std::queue<sf::Event>>>(args[2]).get();

                queue = event_system.processEvents(components);
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
        _eventBus.subscribe(rtype::RTYPE_ACTIONS::CREATE_CLIENT, [](const std::vector<std::any>& args) {
            try {
                unsigned int id = std::any_cast<std::reference_wrapper<unsigned int>>(args[0]).get();
                std::string params = std::any_cast<std::reference_wrapper<std::string>>(args[1]).get();
                std::shared_ptr<ecs::udp::UDP_Client> udpClient = std::any_cast<std::shared_ptr<ecs::udp::UDP_Client>>(args[2]);

                udpClient->setDefaultAddress("127.0.0.0:5000");
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
    }

    void Client::handle_message(std::vector<char>& message, std::string clientAddr)
    {
        ecs::udp::Message mes;
        _message_compressor.deserialize(message, mes);
        _mes_checker.checkAction(mes);
        unsigned int id = mes.id;
        rtype::RTYPE_ACTIONS action = static_cast<rtype::RTYPE_ACTIONS>(mes.action);
        // std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << " body " << mes.body << std::endl;
        _eventBus.emit(action, std::ref(id), std::ref(mes.params), _udpClient);
        std::vector<char> buffer;
        ecs::udp::Message mess;
        mess.id = 78;
        mess.action = 12;
        mess.params = "tg";

        _message_compressor.serialize(mess, buffer);

        _udpClient->sendMessageToDefault(buffer);
    }

    void Client::handle_event()
    {
        while (!_events.empty())
        {
            std::cout << "SIZE : " << _events.size() << std::endl;
            sf::Event event = _events.front();
            _events.pop();
            switch (event.type) {
                case sf::Event::Closed:
                    // DIRE A LA ROOM QUE LE CLIENT SE DECONNECTE
                    _running = false;
                    return;

                case sf::Event::KeyPressed:
                    std::cout << "KEYH PRESSED" << std::endl;
                    if (event.key.code == sf::Keyboard::Escape) {
                        _running = false;
                        return;
                    }
                    if (event.key.code == sf::Keyboard::A) {
                        std::vector<char> buffer;
                        ecs::udp::Message mess;
                        mess.id = 1;
                        mess.action = 0;
                        mess.params = "room_name=room1;client_name=jean";

                        _message_compressor.serialize(mess, buffer);

                        std::cout << "je send" << std::endl;
                        if (_udpClient->sendMessage(buffer, "127.0.0.1:8080")) {
                            std::cout << "Message sent: " << std::endl;
                        } else {
                            std::cout << "failed " << std::endl;
                        }
                    }
                    break;

                case sf::Event::MouseButtonPressed:
                    std::cout << "Bouton de souris appuyé : " << event.mouseButton.button << std::endl;
                    std::cout << "Position de la souris : (" << event.mouseButton.x << ", " << event.mouseButton.y << ")" << std::endl;
                    // Gérer les clics de souris
                    break;

                case sf::Event::Resized:
                    std::cout << "Fenêtre redimensionnée : " << event.size.width << "x" << event.size.height << std::endl;
                    // Gérer le redimensionnement de la fenêtre
                    break;

                default:
                    std::cout << "Événement non traité." << std::endl;
                    break;
            }
        }
    }


    void Client::start()
    {
        size_t index_ecs_client = 0;

        if (!_udpClient->initialize("rtype_game/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeClientExceptions("Failed to initialize client");
        }
        _timer->init("rtype_game/config/client_config.conf", false);
        _udpClient->startReceiving();
        _ecs.init_basic_registry();
        init_ecs_client_registry();
        init_subscribe_event_bus();

        sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
        sf::RenderWindow window(videoMode, "R-Type Client", sf::Style::Fullscreen);

        // Récupère la largeur et la hauteur de la fenêtre SFML
        int width = window.getSize().x;
        int height = window.getSize().y;
        std::string title = "R-Type Client";  // Tu peux changer le titre si nécessaire

        // Crée l'objet rtype::Window avec les paramètres nécessaires
        rtype::Window ecsWindow(width, height, title);
        _ecs.addComponents<Window>(index_ecs_client, ecsWindow);

        sf::Texture backgroundTexture;
        std::cout << "normalement il y a un putain de background pelooooooo" << std::endl;
        if (!backgroundTexture.loadFromFile("assets/background_2.png")) {
            std::cerr << "Erreur de chargement de l'image de fond." << std::endl;
            return;
        }

        sf::Sprite backgroundSprite(backgroundTexture);

        EventWindow event_window;

        // L'initialisation de Window est déjà faite ci-dessus, pas besoin de std::move(window)

        // La boucle du jeu
        while (_running) {
            _timer->waitTPS();
            _eventBus.emit(RTYPE_ACTIONS::CHECK_EVENT_WINDOW, std::ref(event_window), std::ref(_ecs._components_arrays), std::ref(_events));
            handle_event();
            auto messages = _udpClient->fetchAllMessages();
            for (auto &[clientAddress, message] : messages)
            {
                try {
                    handle_message(message, clientAddress);
                } catch (std::exception &e) {
                    std::cerr << std::endl << e.what() << std::endl;
                }
            }
        }
    }
}