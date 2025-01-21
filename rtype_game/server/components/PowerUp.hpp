/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** PowerUp
*/

#ifndef POWERUP_HPP_
    #define POWERUP_HPP_

    #include "../../shared/Includes.hpp"


    namespace rtype
    {
        /**
         * @class PowerUp
         * @brief A class that handles PowerUp in the game.
         */
        class PowerUp {
            public:
                using BonusInfo = std::tuple<bool, std::chrono::steady_clock::time_point, std::chrono::seconds>;

                /**
                 * @brief Constructor of the PowerUp class.
                 */
                PowerUp() {
                    for (int i = VELOCITY; i < MAX_BONUS; ++i) {
                        _bonusMap[static_cast<BONUS>(i)] = std::make_tuple(false, std::chrono::steady_clock::time_point{}, std::chrono::seconds(0));
                    }
                }

                /**
                 * @brief Constructor of the PowerUp class.
                 */
                ~PowerUp() {}

                /**
                 * @brief Activation of the bonus takent by the player.
                 * @param bonus The type of bonus taken
                 * @param duration The time during witch the bonus will be activated
                 */
                void activateBonus(BONUS bonus, int duration) {
                    if (_bonusMap.find(bonus) != _bonusMap.end()) {
                        auto &info = _bonusMap[bonus];
                        std::get<0>(info) = true;
                        std::get<1>(info) = std::chrono::steady_clock::now();
                        std::get<2>(info) = std::chrono::seconds(duration);
                    }
                }

                /**
                 * @brief Update the status of the bonus used by the player.
                 */
                std::list<BONUS> updateBonuses() {
                    auto now = std::chrono::steady_clock::now();
                    std::list<BONUS> finished_bonus;
                    for (auto &[bonus, info] : _bonusMap) {
                        if (std::get<0>(info)) {
                            auto elapsedTime = now - std::get<1>(info);
                            if (elapsedTime >= std::get<2>(info)) {
                                deactivateBonus(bonus);
                                finished_bonus.push_front(bonus);
                            }
                        }
                    }
                    return finished_bonus;
                }

                /**
                 * @brief Desactivate the bonus taken by a player when the duration is over.
                 * @param bonus The type of bonus taken
                 */
                void deactivateBonus(BONUS bonus) {
                    if (_bonusMap.find(bonus) != _bonusMap.end()) {
                        auto &info = _bonusMap[bonus];
                        std::get<0>(info) = false;
                    }
                }

            protected:
            private:
                std::map<BONUS, BonusInfo> _bonusMap;
        };
    }

#endif /* !POWERUP_HPP_ */
