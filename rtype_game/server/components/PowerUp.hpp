/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PowerUp
*/

/**
 * @file PowerUp.hpp
 * @brief Header file for the PowerUp class.
 *
 * This file defines the `PowerUp` class, which manages power-ups (bonuses)
 * available to the player. It tracks the activation and deactivation of bonuses,
 * as well as their duration.
 */

#ifndef POWERUP_HPP_
    #define POWERUP_HPP_

    #include "../../shared/Includes.hpp"

namespace rtype
{
    /**
     * @class PowerUp
     * @brief A class to manage and handle bonuses/power-ups for the player.
     *
     * The `PowerUp` class provides mechanisms to activate, update, and deactivate
     * bonuses. Bonuses may have a duration, and when the duration expires, they
     * are deactivated. The system uses a map to track the state and duration of
     * each bonus.
     */
    class PowerUp {
        public:
            /**
             * @brief Type definition for bonus info.
             * 
             * This is a tuple that holds:
             * 1. A boolean indicating whether the bonus is active or not.
             * 2. The time point when the bonus was activated.
             * 3. The duration of the bonus.
             */
            using BonusInfo = std::tuple<bool, std::chrono::steady_clock::time_point, std::chrono::seconds>;

            /**
             * @brief Default constructor for the PowerUp class.
             * 
             * Initializes all possible bonuses in the `_bonusMap` and sets their
             * initial state as inactive.
             */
            PowerUp() {
                for (int i = VELOCITY; i < MAX_BONUS; ++i) {
                    _bonusMap[static_cast<BONUS>(i)] = std::make_tuple(false, std::chrono::steady_clock::time_point{}, std::chrono::seconds(0));
                }
            }

            /**
             * @brief Destructor for the PowerUp class.
             */
            ~PowerUp() {}

            /**
             * @brief Activates a specific bonus for a given duration.
             * 
             * The bonus is set to active, with the time of activation and the given
             * duration being recorded.
             * 
             * @param bonus The type of bonus to activate.
             * @param duration The duration of the bonus, in seconds.
             */
            void activateBonus(BONUS bonus, int duration) {
                if (_bonusMap.find(bonus) != _bonusMap.end()) {
                    auto &info = _bonusMap[bonus];
                    std::get<0>(info) = true;  ///< Set the bonus as active.
                    std::get<1>(info) = std::chrono::steady_clock::now();  ///< Record the activation time.
                    std::get<2>(info) = std::chrono::seconds(duration);  ///< Set the bonus duration.
                }
            }

            /**
             * @brief Updates all active bonuses and deactivates those that have expired.
             * 
             * Checks the duration of each active bonus. If the bonus has expired,
             * it is deactivated and added to the list of finished bonuses.
             *
             * @return A list of bonuses that have finished (expired).
             */
            std::list<BONUS> updateBonuses() {
                auto now = std::chrono::steady_clock::now();
                std::list<BONUS> finished_bonus;
                for (auto &[bonus, info] : _bonusMap) {
                    if (std::get<0>(info)) {
                        auto elapsedTime = now - std::get<1>(info);
                        if (elapsedTime >= std::get<2>(info)) {
                            deactivateBonus(bonus);
                            finished_bonus.push_front(bonus);  ///< Bonus is expired, deactivate and add to finished.
                        }
                    }
                }
                return finished_bonus;  ///< Return the list of expired bonuses.
            }

            /**
             * @brief Deactivates a specific bonus.
             * 
             * Marks the given bonus as inactive in the `_bonusMap`.
             * 
             * @param bonus The type of bonus to deactivate.
             */
            void deactivateBonus(BONUS bonus) {
                if (_bonusMap.find(bonus) != _bonusMap.end()) {
                    auto &info = _bonusMap[bonus];
                    std::get<0>(info) = false;  ///< Set the bonus as inactive.
                }
            }

        protected:
        private:
            /**
             * @brief A map that holds information about each bonus.
             * 
             * The map stores the bonus type as the key, and a tuple containing:
             * - a boolean indicating if the bonus is active,
             * - the time when the bonus was activated,
             * - the duration of the bonus.
             */
            std::map<BONUS, BonusInfo> _bonusMap;
    };
}

#endif /* !POWERUP_HPP_ */
