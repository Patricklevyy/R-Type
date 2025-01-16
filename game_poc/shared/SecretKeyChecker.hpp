/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SecretKeyChecker
*/

/**
 * @file SecretKeyChecker.hpp
 * @brief Provides functionality for validating secret keys.
 */

#ifndef SECRETKEYCHECKER_HPP_
    #define SECRETKEYCHECKER_HPP_

    #include <iostream>

    namespace poc_game
    {
        /**
         * @class SecretKeyChecker
         * @brief Checks the validity of secret keys for secure communication.
         */
        class SecretKeyChecker {
            public:

                /**
                 * @brief Validates if a sender's key matches the verified key.
                 * @param sender_key The key provided by the sender.
                 * @param verified_key The key expected for verification.
                 * @return True if the keys match, false otherwise.
                 */
                static bool isMessageSafe(const std::string& sender_key, const std::string& verified_key)
                {
                    return sender_key == verified_key;
                }

            protected:
            private:
        };
    }

#endif /* !SECRETKEYCHECKER_HPP_ */
