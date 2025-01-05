/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EventWindow
*/

/**
 * @file EventWindow.hpp
 * @brief Handles event listening and processing.
 */

#ifndef EVENTWINDOW_HPP_
    #define EVENTWINDOW_HPP_

    #include "../components/Window.hpp"
    #include "../../shared/Includes.hpp"
    #include <iostream>
    #include "../../../ecs/SparseArray.hpp"

    namespace poc_game
    {
        /**
        * @brief Manages the event loop and queues events for processing.
        */
        class EventWindow
        {
            public:

                /**
                * @brief Default constructor.
                */
                EventWindow() : isRunning(false) {}

                /**
                 * @brief Destructor, ensures the listener thread is stopped.
                 */
                ~EventWindow() {
                    stopListening();
                }

                /**
                 * @brief Starts the event listening loop in a separate thread.
                 *
                 * @param components_array A reference to the ECS components array.
                 */
                void startListening(std::unordered_map<std::type_index, std::any> &components_array) {
                    isRunning = true;
                    listenerThread = std::thread(&EventWindow::eventLoop, this, std::ref(components_array));
                }

                /**
                 * @brief Stops the event listening loop and joins the thread.
                 */
                void stopListening() {
                    isRunning = false;
                    if (listenerThread.joinable()) {
                        listenerThread.join();
                    }
                }

                /**
                 * @brief Retrieves all queued events.
                 *
                 * @return A queue of SFML events.
                 */
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

                /**
                 * @brief Main event loop that polls events from active windows.
                 *
                 * @param components_array A reference to the ECS components array.
                 */
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
