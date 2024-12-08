/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "Client.hpp"

int main()
{
    rtype::Client RYTPE_CLIENT;

    try
    {
        RYTPE_CLIENT.start();
    }
    catch (std::exception &e)
    {
        std::cerr << std::endl
                  << e.what() << std::endl;
        exit(84);
    }
}
