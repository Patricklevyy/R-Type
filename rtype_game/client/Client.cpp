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
    Client::Client()
    {
    }

    Client::~Client()
    {
    }

    void Client::init_ecs_client_registry()
    {
        _ecs.addRegistry<Window>();
    }

    void Client::init_subscribe_event_bus()
    {
        _eventbus.subscribe(RTYPE_ACTIONS::CHECK_EVENT_WINDOW, [](const std::vector<std::any>& args) {
            try {
                auto& event_system = std::any_cast<std::reference_wrapper<EventWindow>>(args[0]).get();
                auto& components = std::any_cast<std::reference_wrapper<std::unordered_map<std::type_index, std::any>>>(args[1]).get();
                auto& queue = std::any_cast<std::reference_wrapper<std::queue<sf::Event>>>(args[2]).get();

                queue = event_system.processEvents(components);
                std::cout << queue.size() << std::endl;
            } catch (const std::bad_any_cast& e) {
                std::cerr << "Error during event handling: " << e.what() << std::endl;
            }
        });
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
                    if (event.key.code == sf::Keyboard::A) {
                        std::vector<char> buffer;
                        ecs::udp::Message mess;
                        mess.id = 1;
                        mess.action = 0;
                        mess.params = "room_name=room1;client_name=jean";

                        _message_compressor.serialize(mess, buffer);

                        if (udpClient.sendMessage(buffer, "127.0.0.1:8080")) {
                            std::cout << "Message sent: " << std::endl;
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

    void Client::handle_message(std::vector<char>& message, std::string clientAddr)
    {
        ecs::udp::Message mes;
        _message_compressor.deserialize(message, mes);
        _mes_checker.checkAction(mes);
        std::cout << "id : " << mes.id << " action " << mes.action << " params " << mes.params << " body " << mes.body << std::endl;
        exit(84);
    }

    void Client::start()
    {
        size_t index_ecs_client = 0;
        Timer timer;

        if (!udpClient.initialize("rtype_game/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeClientExceptions("Failed to initialize client");
        }
        timer.init("rtype_game/config/client_config.conf", false);
        _ecs.init_basic_registry();
        init_ecs_client_registry();
        init_subscribe_event_bus();
        Window window(800, 600, "My ECS Client Window");
        EventWindow event_window;
        _ecs.addComponents<Window>(index_ecs_client, window);
        udpClient.startReceiving();

        while (_running) {
            timer.waitTPS();
            _eventbus.emit(RTYPE_ACTIONS::CHECK_EVENT_WINDOW, std::ref(event_window), std::ref(_ecs._components_arrays), std::ref(_events));
            handle_event();
            auto messages = udpClient.fetchAllMessages();
            for (auto &[clientAddress, message] : messages)
            {
                try {
                    handle_message(message, clientAddress);
                } catch (std::exception &e) {
                    std::cerr << std::endl << e.what() << std::endl;
                }
            }
        }
        // // Boucle principale
        // while (window.isRunning())
        // {
        //     // Mise à jour et collecte des événements
        //     window.updateEvent();

        //     // Traiter les événements
        //     auto events = window.fetchEvents();
        //     while (!events.empty())
        //     {
        //         auto event = events.front();
        //         events.pop();

        //         // Exemple de traitement
        //         if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        //         {
        //             std::cout << "Escape pressed! Closing window." << std::endl;
        //             break;
        //         }
        //     }
        // }
        // Window window(800, 600, "RTYPE");
        // EventWindow eventSystem;

        // // Boucle principale
        // while (window.isRunning()) {
        //     // Mise à jour de la fenêtre (collecte des événements)
        //     window.update();

        //     // Traite les événements collectés
        //     eventSystem.processEvents(window);

        //     // Autres systèmes ou logique de jeu ici
        // }
    }
//         ecs::udp::UDP_Client udpClient;

//     if (!udpClient.initialize("rtype_game/config/udp_config.conf")) {
//         std::cerr << "Client initialization failed." << std::endl;
//         return 1;
//     }

//     std::string message = "CREATE";

//     std::vector<char> buffer;
//     ecs::udp::Message mess;
//     mess.id = 1;
//     mess.action = 0;
//     mess.params = "room_name=room1;client_name=jean";

//     ecs::udp::MessageCompressor compresor;

//     compresor.serialize(mess, buffer);

//     if (udpClient.sendMessage(buffer, "127.0.0.1:8080")) {
//         std::cout << "Message sent: " << message << std::endl;
//     } else {
//         std::cerr << "Failed to send message." << std::endl;
//         return 1;
//     }

//     std::cout << "Waiting for response from the server..." << std::endl;

//     std::string response;
//     bool messageReceived = false;
//     std::string roomAddress;

//     for (int i = 0; i < 10; ++i) {
//         if (udpClient.receiveMessage(response)) {
//             std::cout << "Received response: " << response << std::endl;

//             if (response.find("The room address is:") != std::string::npos) {
//                 size_t pos = response.find("The room address is:") + std::strlen("The room address is: ");
//                 roomAddress = response.substr(pos);
//                 std::cout << "Room address received: " << roomAddress << std::endl;

//                 if (udpClient.sendMessage("Received room address: " + roomAddress, "127.0.0.1:8080")) {
//                     std::cout << "Message with room address sent to server." << std::endl;
//                 } else {
//                     std::cerr << "Failed to send room address back to the server." << std::endl;
//                 }
//             }
//             messageReceived = true;
//             break;
//         } else {
//             std::cerr << "Failed to receive response. Retrying..." << std::endl;
//             usleep(500000);
//         }
//     }

//     if (!messageReceived) {
//         std::cerr << "Server not available or no response received after several retries." << std::endl;
//     }

//     return 0;
// }
}