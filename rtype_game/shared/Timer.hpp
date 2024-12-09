/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Timer
*/

#ifndef TIMER_HPP_
    #define TIMER_HPP_

    #include "Includes.hpp"

    namespace rtype
    {
        class Timer {
        public:
            Timer();
            ~Timer();

            void init(const std::string& configFile, bool isServer);

            void waitTPS();
            void waitFPS();

        private:
            std::chrono::duration<float> tps_duration;
            std::chrono::duration<float> fps_duration;
            std::chrono::time_point<std::chrono::high_resolution_clock> last_tps_tick;
            std::chrono::time_point<std::chrono::high_resolution_clock> last_fps_tick;
        };

    }

#endif /* !TIMER_HPP_ */
