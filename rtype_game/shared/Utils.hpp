/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <iostream>
    #include "../../ecs/Enums_ecs.hpp"
    #include <vector>
    #include <tuple>
    #include <sstream>
    #include "Enums.hpp"
    #include "RTypeExceptions.hpp"
    #include "Includes.hpp"
    #include <list>
    #include "../../ecs/components/Direction.hpp"

    namespace rtype
    {
        /**
         * @class Utils
         * @brief A utility class providing static methods for parsingand sending informations.
         */
        class Utils {
            public:
                /**
                 * @brief Parse a string of parameters into a map.
                 * @param params A string containing parameters in a specific format.
                 * @return A map of key-value pairs extracted from the string.
                 */
                static std::map<std::string, std::string> parseMessageParams(const std::string &params);

                /**
                 * @brief Validate an action identifier.
                 * @param action An integer representing the action to check.
                 */
                static void checkAction(int);

                /**
                 * @brief Extract the player's position, direction, and index from a string message.
                 * @param data A string containing player information.
                 * @param index An unsigned integer identifying the player.
                 * @return A tuple containing two directions and a size_t index.
                 */
                static std::tuple<ecs::direction, ecs::direction, size_t> extractPlayerPosIndex(std::string, unsigned int);

                /**
                 * @brief Extract the projectile's position, direction, and sprite type from a string.
                 * @param data A string containing projectile information.
                 * @return A tuple containing:
                 * - A pair of floats representing the position.
                 * - A pair of integers representing the direction.
                 * - SPRITES enum representing the sprite type.
                 */
                static std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES> extractProjectilePosAndDir(std::string);

                /**
                 * @brief Check if the given sprite type represents an ally.
                 * @param type SPRITES enum representing the sprite type.
                 * @return True if the sprite is an ally, false otherwise.
                 */
                static bool isAllie(SPRITES type);

                /**
                 * @brief Convert projectile information to a string.
                 * @param projectileInfo A tuple containing projectile data.
                 * @param velocity An integer representing the velocity of the projectile.
                 * @return A string representation of the projectile information.
                 */
                static std::string projectilesInfoToString(std::tuple<std::pair<float, float>, std::pair<int, int>, SPRITES>, int);

                /**
                 * @brief Convert bonus information to a string.
                 * @param position A pair of floats representing the position.
                 * @param direction_x An integer representing the x direction.
                 * @param direction_y An integer representing the y direction.
                 * @param sprite SPRITES enum representing the sprite type.
                 * @param velocity An integer representing the speed of the bonus.
                 * @return A string representing of the bonus information.
                 */
                static std::string bonusInfoToString(const std::pair<float, float> &position, int direction_x, int direction_y, SPRITES sprite, int velocity);

                /**
                 * @brief Validate and format an address string.
                 * @param port An integer representing the port number.
                 * @param address A string containing the address.
                 * @return A validated and formatted address string.
                 */
                static std::string check_adress(int, const std::string&);

                /**
                 * @brief Parse an update message into a list of entities and their positions.
                 * @param update A string containing update information.
                 * @return A list of pairs, where each pair consists of:
                 * - A size_t index representing the entity.
                 * - A pair of floats representing the position.
                 */
                static std::list<std::pair<std::size_t, std::pair<float, float>>> parse_update(const std::string&);

                /**
                 * @brief Parse an update message into a vector of entity data.
                 * @param update A string containing update information.
                 * @return A vector of tuples, where each tuple contains:
                 * - A pair of floats representing the position.
                 * - Two integers representing additional data.
                 */
                static std::vector<std::tuple<std::pair<float, float>, int, int>> parseUpdateEntities(const std::string&);

                /**
                 * @brief Parse position and room port information from a string.
                 * @param data A string containing position and port information.
                 * @return A tuple containing:
                 * - A tuple of floats and an integer.
                 * - Two integers representing the port and other data.
                 */
                static std::tuple<std::tuple<float, float, int>, int, int> parsePositionAndRoomPort(const std::string &);

                /**
                 * @brief Parse an update message for life values.
                 * @param update A string containing life update information.
                 * @return A list of pairs, where each pair consists of:
                 * - A size_t index representing the entity.
                 * - An integer representing the life value.
                 */
                static std::list<std::pair<std::size_t, int>> parse_update_life(const std::string &);
            protected:
            private:
        };
    }

#endif /* !UTILS_HPP_ */
