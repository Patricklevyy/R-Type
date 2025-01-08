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
    #include <vector>

    namespace rtype
    {
        class Command_checker
        {
        public:
            static std::string check_adress(int, const std::string&);
            static std::list<std::pair<std::size_t, std::pair<float, float>>> parse_update(const std::string&);
            static std::vector<std::tuple<std::pair<float, float>, int, int>> parseUpdateEntities(const std::string&);
            static std::tuple<float, float, int> parsePositionAndRoomPort(const std::string &);

        protected:
        private:
        };
    }
#endif /* !COMMAND_CHECKER_HPP_ */
