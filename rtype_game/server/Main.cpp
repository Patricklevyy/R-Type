/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "Server.hpp"

int main() {
    rtype::Server RYTPE_SERVER;

    int response = RYTPE_SERVER.start();

    std::cout << "RESPONSE " << response << std::endl;
}
