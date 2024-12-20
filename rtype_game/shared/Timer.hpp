/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Timer
*/

/**
 * @file Timer.hpp
 * @brief Manages time-related functionalities such as ticks per second (TPS) and frames per second (FPS).
 */

#ifndef TIMER_HPP_
    #define TIMER_HPP_

    #include "Includes.hpp"

    namespace rtype
    {
        /**
         * @class Timer
         * @brief Handles timing for the game loop and frame updates.
         */
        class Timer {
        public:
            Timer();
            ~Timer();

            /**
             * @brief Initializes the timer with configuration settings.
             * @param configFile Path to the configuration file.
             * @param isServer Indicates whether the timer is used on the server side.
             */
            void init(const std::string& configFile, bool isServer);

            /**
             * @brief Waits for the next tick to maintain TPS.
             */
            void waitTPS();

            /**
             * @brief Waits for the next frame to maintain FPS.
             */
            void waitFPS();

            /**
             * @brief Gets the current TPS value.
             * @return The TPS value.
             */
            float getTps() const;

        private:
            float _tps;
            std::chrono::duration<float> tps_duration;
            std::chrono::duration<float> fps_duration;
            std::chrono::time_point<std::chrono::high_resolution_clock> last_tps_tick;
            std::chrono::time_point<std::chrono::high_resolution_clock> last_fps_tick;
        };

    }

#endif /* !TIMER_HPP_ */
