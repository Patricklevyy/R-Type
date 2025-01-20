/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Utils
*/

/**
 * @file Utils.hpp
 * @brief Utility class that provides various helper functions for the game logic.
 */

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <iostream>
    #include "../../ecs/Enums_ecs.hpp"
    #include <vector>
    #include <tuple>
    #include <sstream>
    #include "Enums.hpp"
    #include "PocExceptions.hpp"
    #include "Includes.hpp"
    #include <list>

    namespace poc_game
    {
        /**
         * @brief Utility class that provides various helper functions for the game logic.
         * 
         * This class contains static utility methods for parsing messages, extracting data,
         * and other operations related to the game.
         */
        class Utils {
            public:
                /**
                 * @brief Parses message parameters from a given string.
                 * 
                 * This method processes a string representing parameters (like key-value pairs),
                 * extracting and returning them as a map where keys and values are strings.
                 * 
                 * @param params A string containing the message parameters to parse.
                 * @return A map where the key is a string representing the parameter name, and the value is the parameter's value.
                 */
                static std::map<std::string, std::string> parseMessageParams(const std::string &params);

                /**
                 * @brief Validates an action based on its ID.
                 * 
                 * This function checks if an action, identified by its integer ID, is valid.
                 * 
                 * @param actionID The action ID to validate.
                 */
                static void checkAction(int actionID);

                /**
                 * @brief Extracts the player's position and index.
                 * 
                 * This method processes a string and extracts the player's direction (two directions)
                 * and their index as part of a tuple for later use in the game logic.
                 * 
                 * @param input A string containing the necessary data to extract the player's info.
                 * @param someValue An unsigned integer that might be part of the extraction logic.
                 * @return A tuple containing two directions (`ecs::direction`), and the player's index as a size_t.
                 */
                static std::tuple<ecs::direction, ecs::direction, size_t> extractPlayerPosIndex(std::string input, unsigned int someValue);

                /**
                 * @brief Extracts projectile position, direction, and sprite type.
                 * 
                 * This method extracts the position (as a pair of floats), the direction (as a pair of ints),
                 * and the sprite associated with the projectile from a string.
                 * 
                 * @param input A string containing the necessary data to extract the projectile info.
                 * @return A tuple containing the projectile position, direction, and sprite.
                 */
                static std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> extractProjectilePosAndDir(std::string input);

                /**
                 * @brief Determines if a given sprite type is classified as an ally.
                 * 
                 * This method checks if a specific sprite type represents an ally.
                 * 
                 * @param type The sprite type (represented by `SPRITES`).
                 * @return True if the sprite is classified as an ally, false otherwise.
                 */
                static bool isAllie(SPRITES type);

                /**
                 * @brief Converts projectile information to a string representation.
                 * 
                 * This method converts a tuple containing projectile info (position, direction, sprite)
                 * into a human-readable string.
                 * 
                 * @param info The tuple containing projectile information (position, direction, sprite).
                 * @param id An integer associated with the projectile.
                 * @return A string representation of the projectile info.
                 */
                static std::string projectilesInfoToString(std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> info, int id);

                /**
                 * @brief Parses position and room port from a given string.
                 * 
                 * This method extracts the position (as two floats) and the room port (as an integer)
                 * from a string.
                 * 
                 * @param input The string containing the position and room port information.
                 * @return A tuple containing two floats for position and an integer for room port.
                 */
                static std::tuple<float, float, int> parsePositionAndRoomPort(const std::string &input);

                /**
                 * @brief Checks an address for validity or resolves it.
                 * 
                 * This method validates the address or resolves it based on the provided
                 * address and port.
                 * 
                 * @param port An integer representing the port to check.
                 * @param address The address to check or resolve.
                 * @return A string representation of the valid/resolved address.
                 */
                static std::string check_adress(int port, const std::string &address);

                /**
                 * @brief Parses an update string and returns a list of tuples representing entity states.
                 * 
                 * This method processes a string representing updates and extracts information
                 * for each entity (ID, position data, etc.), returning it as a list of tuples.
                 * 
                 * @param input The string containing update information.
                 * @return A list of tuples, each containing an entity index and position data (float, float).
                 */
                static std::list<std::tuple<std::size_t, float, float>> parse_update(const std::string &input);
            protected:
            private:
        };
    }

#endif /* !UTILS_HPP_ */
