/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "Client.hpp"
#include "menu/menu.hpp"

int main()
{
    try {
        rtype::Menu menu(800, 600, "R-Type Menu");
        menu.run();

    }
    catch (const std::exception &e) {
        std::cerr << std::endl
                  << e.what() << std::endl;
        return 84;
    }

    return 0;
}