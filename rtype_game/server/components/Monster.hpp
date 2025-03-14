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

        /**
         * @class Monster
         * @brief A class that handles Monsters in the game.
         */
        class Monster {
        public:
            /**
             * @brief Constructor of the Monster class.
             * @param type The type of sprite that will be use for the monster
             * @param score_value The value that will be given to the player when the monster will be kill
             */
            Monster(SPRITES type, int score_value = 1) : _intValue(5), _monster(type), _score_value(score_value)

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
            int _score_value;

        protected:
        private:
            std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        };

    }

#endif /* !MONSTER_HPP_ */
