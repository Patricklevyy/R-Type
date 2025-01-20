/*
** EPITECH PROJECT, 2025
** R-TYPE
** File description:
** Main
*/

#include "Client.hpp"

int main()
{
    poc_game::Client POC_GAME_CLIENT;

    try {
        POC_GAME_CLIENT.start();
    } catch (std::exception &e) {
        std::cerr << std::endl << e.what() << std::endl;
        exit(84);
    }
}