/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Main
*/

#include "Client.hpp"
#include "system/menuSystem.hpp"
#include "../ecs/ECS.hpp"

int main() {
    try {
        // Initialiser l'ECS
        ecs::ECS ecs;
        ecs.init_basic_registry();

        // Lancer le menu
        rtype::MenuSystem menu_system;
        menu_system.start(ecs._components_arrays);

        // Si le menu se termine, démarrer le client
        rtype::Client client;
        client.start();

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    return 0;
}

