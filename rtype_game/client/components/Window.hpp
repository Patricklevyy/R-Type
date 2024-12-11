/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Window
*/

/**
 * @file Window.hpp
 * @brief Define the Window component
 */

#ifndef WINDOW_HPP_
    #define WINDOW_HPP_

    #include <SFML/Graphics.hpp>
    #include <queue>
    #include <mutex>
    #include <memory>

    namespace rtype
    {

    /**
     * @class Window
     * @brief Manages an SFML window and event queue for rendering and input handling.
     */
    class Window
    {
    public:
        /**
         * @brief Constructs a new Window object.
         * @param width Width of the window.
         * @param height Height of the window.
         * @param title Title of the window.
         */
        Window(int width, int height, const std::string& title)
        {
            window = std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), title);
        }

        /**
         * @brief Destructor for the Window class.
         */
        ~Window() {}

        /**
         * @brief Updates the event queue by polling events from the SFML window.
         */
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

        /**
         * @brief Retrieves and clears the current event queue.
         * @return A queue containing all pending events.
         */
        std::queue<sf::Event> fetchEvents()
        {
            std::queue<sf::Event> events = std::move(eventQueue);
            eventQueue = {};
            return events;
        }

        /**
         * @brief Checks if the window is still running.
         * @return True if the window is open, false otherwise.
         */
        bool isRunning() const
        {
            return isOpen;
        }

        /**
         * @brief Gets the underlying SFML RenderWindow.
         * @return A shared pointer to the SFML RenderWindow.
         */
        std::shared_ptr<sf::RenderWindow> getRenderWindow()
        {
            return window;
        }

    private:
        std::shared_ptr<sf::RenderWindow> window; /**< SFML RenderWindow instance. */
        std::queue<sf::Event> eventQueue; /**< Queue of SFML events. */
        bool isOpen; /**< Flag indicating if the window is open. */
    };
}

#endif /* !WINDOW_HPP_ */
