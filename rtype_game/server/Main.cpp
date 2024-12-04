/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

// #include "Server.hpp"

#include "../../ecs/ECS.hpp"
#include "../../ecs/components/Position.hpp"
#include "../../ecs/components/Velocity.hpp"
// int main() {
//     rtype::Server RYTPE_SERVER;

//     try {
//         RYTPE_SERVER.start();
//     } catch (std::exception &e) {
//         std::cerr << std::endl << e.what() << std::endl;
//         exit(84);
//     }
// }

int main() {
    ecs::ECS ecs;

    // Enregistrer des types de composants
    ecs.addRegistry<ecs::Position>();

    try {
        ecs::Velocity vel;
        vel.velocity = 12.5;
    } catch (std::exception &e) {
        std::cerr << std::endl << e.what() << std::endl;
    }
    ecs.addRegistry<ecs::Velocity>();  // Enregistre un tableau pour des flottants

    ecs::Position pos;
    pos.pos_x = 47;
    pos.pos_y = 100;

    ecs::Velocity vel;
    vel.velocity = 12.5;

    try {
        ecs.addComponents<ecs::Position>(2, pos);
    } catch (std::exception &e) {
        std::cerr << std::endl << e.what() << std::endl;
    }
    return 0;
}
