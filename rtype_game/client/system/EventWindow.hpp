/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EventWindow
*/

#ifndef EVENTWINDOW_HPP_
    #define EVENTWINDOW_HPP_

    #include "../components/Window.hpp"
    #include "../../shared/Includes.hpp"
    #include <iostream>
    #include "../../../ecs/SparseArray.hpp"

    namespace rtype
    {
        class EventWindow
        {
            public:
                EventWindow() : isRunning(false) {}

                ~EventWindow() {
                    stopListening();
                }

                void startListening(std::unordered_map<std::type_index, std::any> &components_array) {
                    isRunning = true;
                    listenerThread = std::thread(&EventWindow::eventLoop, this, std::ref(components_array));
                }

                void stopListening() {
                    isRunning = false;
                    if (listenerThread.joinable()) {
                        listenerThread.join();
                    }
                }

                std::queue<sf::Event> fetchEvents() {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    std::queue<sf::Event> events = std::move(eventQueue);
                    eventQueue = {};
                    return events;
                }

            private:
                std::atomic<bool> isRunning;
                std::thread listenerThread;
                std::queue<sf::Event> eventQueue;
                std::mutex queueMutex;

                void eventLoop(std::unordered_map<std::type_index, std::any> &components_array) {
                    while (isRunning) {
                        auto &windowArray = std::any_cast<ecs::SparseArray<Window> &>(components_array[typeid(Window)]);

                        for (std::size_t i = 0; i < windowArray.size(); ++i) {
                            if (windowArray[i].has_value()) {
                                auto &window = windowArray[i].value();

                                if (window.getRenderWindow()->isOpen()) {
                                    sf::Event event;
                                    while (window.getRenderWindow()->pollEvent(event)) {
                                        std::lock_guard<std::mutex> lock(queueMutex);
                                        eventQueue.push(event);
                                    }
                                }
                            }
                        }

                        std::this_thread::sleep_for(std::chrono::milliseconds(10));
                    }
                }
            };
    }

#endif /* !EVENTWINDOW_HPP_ */
