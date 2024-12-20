/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EventBus
*/

/**
 * @file EventBus.hpp
 * @brief Implements an event bus system for handling game events and actions.
 */

#ifndef EVENTBUS_HPP_
    #define EVENTBUS_HPP_

    #include "Includes.hpp"

    namespace rtype
    {
        /**
         * @class EventBus
         * @brief A system for subscribing and emitting events in the game.
         */
        class EventBus
        {
        public:
            /**
             * @brief Subscribes a listener to a specific event type.
             * @param type The type of the event.
             * @param listener The function to call when the event is emitted.
             */
            void subscribe(RTYPE_ACTIONS type, std::function<void(const std::vector<std::any> &)> listener)
            {
                subscribers[type].push_back(listener);
            }

            /**
             * @brief Emits an event of a specific type, passing arguments to the listeners.
             * @tparam Args Variadic template for arguments to pass to the listeners.
             * @param type The type of the event.
             * @param args Arguments to pass to the listeners.
             */
            template <typename... Args>
            void emit(RTYPE_ACTIONS type, Args &&...args)
            {
                auto it = subscribers.find(type);
                if (it != subscribers.end())
                {
                    std::vector<std::any> anyArgs = {std::forward<Args>(args)...};
                    for (auto &listener : it->second)
                    {
                        listener(anyArgs);
                    }
                }
            }

        private:
            std::unordered_map<RTYPE_ACTIONS, std::vector<std::function<void(const std::vector<std::any> &)>>> subscribers;
        };
    }

#endif /* !EVENTBUS_HPP_ */
