/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include <SFML/Graphics.hpp>
    #include <queue>
    #include <mutex>
    #include <memory>

    namespace rtype
    {

        class Window
    {
    public:
        Window(int width, int height, const std::string& title)
        {
            window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
        }

        ~Window() {}

        void updateEvent()
        {
            if (window->isOpen())
            {
                sf::Event event;

                if (window->pollEvent(event))
                {
                    eventQueue.push(event);
                }
            }
        }

        std::queue<sf::Event> fetchEvents()
        {
            std::queue<sf::Event> events = std::move(eventQueue);
            eventQueue = {};
            return events;
        }

        bool isRunning() const
        {
            return isOpen;
        }

        std::shared_ptr<sf::RenderWindow> getRenderWindow()
        {
            return window;
        }

    private:
        std::shared_ptr<sf::RenderWindow> window;
        std::queue<sf::Event> eventQueue;
        bool isOpen;
    };
}

#endif /* !WINDOW_HPP_ */
