/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Monster
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

            ~Monster() {}

            void setTimer(int seconds) {
                _intValue = seconds;
            }

            int getIntValue() const {
                return _intValue;
            }

            void setIntValue(int value) {
                _intValue = value;
            }

            double getElapsedTime() const {
                auto currentTime = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = currentTime - startTime;
                return elapsed.count();
            }

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
