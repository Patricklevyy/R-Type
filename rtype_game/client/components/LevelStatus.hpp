/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** LevelStatus
*/

#ifndef LEVELSTATUS_HPP_
    #define LEVELSTATUS_HPP_

    /**
     * @file LevelStatus.hpp
     * @brief Header file for the LevelStatus class.
     * 
     * This file contains the declaration of the LevelStatus class, which is part of the rtype namespace.
     */

    namespace rtype
    {
        /**
         * @class LevelStatus
         * @brief Represents the status of a level in the game.
         * 
         * The LevelStatus class is used to manage and track the status of a level in the R-Type game.
         */
        class LevelStatus {
            public:
                /**
                 * @brief Default constructor for LevelStatus.
                 * 
                 * Initializes a new instance of the LevelStatus class.
                 */
                LevelStatus();

                /**
                 * @brief Destructor for LevelStatus.
                 * 
                 * Cleans up any resources used by the LevelStatus instance.
                 */
                ~LevelStatus();

            protected:
            private:
        };
    }

#endif /* !LEVELSTATUS_HPP_ */
