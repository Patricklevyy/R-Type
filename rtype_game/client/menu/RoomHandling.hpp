/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** RoomHandling
*/

/**
 * @file RoomHandling.hpp
 * @brief Provides the definition of the RoomHandling class for managing and rendering game rooms.
 * 
 * This file defines the RoomHandling class, which is responsible for handling 
 * the list of game rooms, managing user interactions with these rooms, and rendering 
 * the room list on the screen.
 */

#ifndef ROOMHANDLING_HPP_
#define ROOMHANDLING_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <unordered_set>

namespace rtype
{
    /**
     * @class RoomHandling
     * @brief Manages the list of rooms and user interactions with them.
     * 
     * The RoomHandling class provides functionality to:
     * - Add rooms to a room list.
     * - Handle clicks on room names.
     * - Scroll through a list of rooms.
     * - Render the list of rooms within a graphical container.
     * 
     * The class operates on a reference to a vector of rooms, each represented as a
     * pair containing the room name and the number of current players.
     */
    class RoomHandling {
      public:
        /**
         * @brief Constructs a new RoomHandling object.
         * 
         * @param _font Reference to the font used for rendering text.
         * @param rooms Reference to a vector of pairs representing room names and player counts.
         */
        RoomHandling(sf::Font &_font, std::vector<std::pair<std::string, int>> &rooms)
        : _rooms(rooms), _font(_font), _scrollOffset(0) {};
        
        /**
         * @brief Destructor for RoomHandling.
         */
        ~RoomHandling() {};

        /**
         * @brief Adds a room to the list of rooms.
         * 
         * @param name The name of the new room.
         * @param nb_places The number of players in the room.
         */
        void addRoom(const std::string &name, int nb_places)
        {
            _rooms.emplace_back(name, nb_places);
        }

        /**
         * @brief Handles clicks on rooms.
         * 
         * Checks if a given mouse position is within the bounds of a room's clickable area.
         * If so, the selected room is updated and returned.
         * 
         * @param mousePos The position of the mouse click.
         * @param container The container that bounds the list of rooms.
         * @return The name of the selected room, or an empty string if no room was selected.
         */
        std::string handleClick(
            const sf::Vector2f &mousePos, const sf::RectangleShape &container);

        /**
         * @brief Handles scrolling within the list of rooms.
         * 
         * Adjusts the scroll offset by a delta value, keeping it within valid bounds.
         * 
         * @param delta The amount to scroll (positive or negative).
         */
        void handleScroll(float delta)
        {
            _scrollOffset += delta * 20;
            if (_scrollOffset < 0)
                _scrollOffset = 0;
        }

        /**
         * @brief Draws the list of rooms within a container.
         * 
         * Renders each room that falls within the visible area of the container. Rooms
         * are displayed as rectangles with their names and player counts.
         * 
         * @param window The window to render the rooms into.
         * @param container The container bounding the room list.
         */
        void draw(sf::RenderWindow &window, const sf::RectangleShape &container);

        /**
         * @brief Gets the currently selected room.
         * 
         * @return The name of the currently selected room, or an empty string if none is selected.
         */
        std::string getSelectedRoom() const
        {
            return _selectedRoom;
        }

        /**
         * @brief Reference to the list of rooms.
         * 
         * Each room is represented as a pair of a room name and a player count.
         */
        std::vector<std::pair<std::string, int>> &_rooms;

      protected:
      private:
        sf::Font &_font; ///< Reference to the font used for room text rendering.
        float _scrollOffset; ///< Offset for scrolling through the room list.
        std::string _selectedRoom; ///< Name of the currently selected room.
    };
} // namespace rtype

#endif /* !ROOMHANDLING_HPP_ */
