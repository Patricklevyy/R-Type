/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Command_checker
*/

#ifndef COMMAND_CHECKER_HPP_
    #define COMMAND_CHECKER_HPP_

    #include <iostream>
    #include <map>
    #include "../shared/RTypeExceptions.hpp"

    namespace rtype
    {
        class Command_checker
        {
        public:
            static std::string check_adress(std::map<std::string, std::string>&);

        protected:
        private:
        };
    }
#endif /* !COMMAND_CHECKER_HPP_ */
