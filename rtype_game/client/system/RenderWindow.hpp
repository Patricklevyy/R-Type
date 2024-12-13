/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderWindow
*/

#ifndef RENDERWINDOW_HPP_
    #define RENDERWINDOW_HPP_

    #include "../components/Window.hpp"
    #include "../components/Background.hpp"
    #include "../../shared/Includes.hpp"
    #include <iostream>
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Displayable.hpp"
    #include "../../../ecs/components/Position.hpp"

    namespace rtype
    {
        class RenderWindow
        {
            public:

                void render(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    try {
                        std::cout << "con" << std::endl;
                        auto &displayable = std::any_cast<ecs::SparseArray<ecs::Displayable> &>(components_array.at(typeid(ecs::Displayable)));
                        auto &windows = std::any_cast<ecs::SparseArray<Window> &>(components_array.at(typeid(Window)));
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array.at(typeid(ecs::Position)));

                        auto lawindow = windows[0].value().getRenderWindow().get();
                        lawindow->clear(sf::Color::Yellow);
                        for (size_t i = 0; i < displayable.size(); ++i) {
                            if (displayable[i].has_value() && positions[i].has_value()) {
                                displayable[i].value().setSpritePosition(positions[i].value()._pos_x, positions[i].value()._pos_y);
                                lawindow->draw(displayable[i].value().getSprite());

                                std::cout << "[INFO] Rendu terminé pour l'entité " << i << std::endl;
                            } else {
                                std::cout << "[WARNING] Fenêtre ou background invalide à l'index " << i << std::endl;
                            }
                        }
                        lawindow->display();
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }
            private:
        };
    }

#endif /* !RENDERWINDOW_HPP_ */