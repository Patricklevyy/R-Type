/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Monster
*/

/**
 * @file Monster.hpp
 * @brief Class representing a monster entity.
 *
 * The Monster class includes functionality for managing the monster's attributes and behavior.
 */

#ifndef MONSTER_HPP_
    #define MONSTER_HPP_

    namespace rtype {
        #include <chrono>

        class Monster {
        public:
            Monster(SPRITES type) : _intValue(5), _monster(type)

            {
                startTime = std::chrono::high_resolution_clock::now();
            }

            /**
             * @brief Destructor for the Monster class.
             */
            ~Monster() {}

            /**
             * @brief Sets the timer duration for the monster.
             * @param seconds The duration in seconds.
             */
            void setTimer(int seconds) {
                _intValue = seconds;
            }

            /**
             * @brief Gets the current integer value.
             * @return The integer value.
             */
            int getIntValue() const {
                return _intValue;
            }

            /**
             * @brief Sets a new integer value.
             * @param value The new value to set.
             */
            void setIntValue(int value) {
                _intValue = value;
            }

            /**
             * @brief Gets the elapsed time since the timer started.
             * @return The elapsed time in seconds.
             */
            double getElapsedTime() const {
                auto currentTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = currentTime - startTime;
                return elapsed.count();
            }

            /**
             * @brief Resets the timer to the current time.
             */
            void resetTimer() {
                startTime = std::chrono::high_resolution_clock::now();
            }

            int _intValue;
            SPRITES _monster;

        protected:
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        };

    }

#endif /* !MONSTER_HPP_ */
