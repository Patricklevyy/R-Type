/*
** EPITECH PROJECT, 2025
** R-TYPE
** File description:
** Main
*/

#include "Server.hpp"

int main()
{
    poc_game::Server POC_SERVER;

    try {
        POC_SERVER.start();
    } catch (std::exception &e) {
        std::cerr << std::endl << e.what() << std::endl;
        exit(84);
    }
}
