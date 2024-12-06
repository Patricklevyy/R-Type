/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MessageChecker
*/

#ifndef MESSAGECHECKER_HPP_
    #define MESSAGECHECKER_HPP_

    #include "../shared/Includes.hpp"
    #include "../../ecs/udp/MessageCompressor.hpp"

    namespace rtype
    {
        class MessageChecker {
            public:
                MessageChecker();
                ~MessageChecker();

                void checkAction(const ecs::udp::Message&) const;

                std::map<std::string, std::string> checkFormatParams(std::string&);

            protected:
            private:
        };
    }

#endif /* !MESSAGECHECKER_HPP_ */
