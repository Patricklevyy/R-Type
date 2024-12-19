/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SecretKeyChecker
*/

#ifndef SECRETKEYCHECKER_HPP_
    #define SECRETKEYCHECKER_HPP_

    #include <iostream>

    namespace rtype
    {
       class SecretKeyChecker {
            public:
                static bool isMessageSafe(const std::string& sender_key, const std::string& verified_key)
                {
                    return sender_key == verified_key;
                }

            protected:
            private:
        };
    }

#endif /* !SECRETKEYCHECKER_HPP_ */
