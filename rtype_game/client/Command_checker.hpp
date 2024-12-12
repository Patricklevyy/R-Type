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
    #include <list>
    #include <sstream>
    #include <utility>
    #include <cstdlib>

    namespace rtype
    {
        class Command_checker
        {
        public:
            static std::string check_adress(std::map<std::string, std::string>&, std::string);
            static std::list<std::tuple<std::size_t, std::pair<float, float>, int>> parse_update(std::string);

        protected:
        private:
        };
    }
#endif /* !COMMAND_CHECKER_HPP_ */
