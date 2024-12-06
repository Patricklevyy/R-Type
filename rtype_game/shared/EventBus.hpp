/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EventBus
*/

#ifndef EVENTBUS_HPP_
    #define EVENTBUS_HPP_

    #include "Includes.hpp"

    namespace rtype
    {
        class EventBus {
            public:
                void subscribe(RTYPE_ACTIONS type, std::function<void(const std::vector<std::any>&)> listener) {
                    subscribers[type].push_back(listener);
                }

                template <typename... Args>
                void emit(RTYPE_ACTIONS type, Args&&... args) {
                    auto it = subscribers.find(type);
                    if (it != subscribers.end()) {
                        std::vector<std::any> anyArgs = {std::forward<Args>(args)...};
                        for (auto& listener : it->second) {
                            listener(anyArgs);
                        }
                    }
                }

            private:
                std::unordered_map<RTYPE_ACTIONS, std::vector<std::function<void(const std::vector<std::any>&)>>> subscribers;
            };
    }

#endif /* !EVENTBUS_HPP_ */
