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
                /**
                * @brief Processes events from all windows in the ECS components array.
                * @param components_array A map containing ECS components by type.
                * @return A queue of events from the processed windows.
                */
                std::queue<sf::Event> processEvents(std::unordered_map<std::type_index, std::any> &components_array) {
                    auto &window = std::any_cast<ecs::SparseArray<Window> &>(components_array[typeid(Window)]);

                    for (std::size_t i = 0; i < window.size(); ++i)
                    {
                        if (window[i].has_value()) {
                            window[i].value().updateEvent();
                            return window[i].value().fetchEvents();
                        }
                    }
                    std::queue<sf::Event> queue;
                    return queue;
                }
        };
    }

#endif /* !EVENTWINDOW_HPP_ */
