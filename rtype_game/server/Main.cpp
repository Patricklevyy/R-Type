/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "Server.hpp"

int main() {
    rtype::Server RYTPE_SERVER;

    try {
        RYTPE_SERVER.start();
    } catch (std::exception &e) {
        std::cerr << std::endl << e.what() << std::endl;
        exit(84);
    }
}
