/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RenderWindow
*/


/**
 * @file RenderWindow.hpp
 * @brief Responsible for rendering entities, backgrounds, and applying shaders to the game window.
 */

#ifndef RENDERWINDOW_HPP_
    #define RENDERWINDOW_HPP_

    #include "../components/Window.hpp"
    #include "../components/Background.hpp"
    #include "../components/Shader.hpp"
    #include "../../shared/Includes.hpp"
    #include <iostream>
    #include "../../../ecs/SparseArray.hpp"
    #include "../components/Displayable.hpp"
    #include "./SetFilter.hpp"
    #include "../../../ecs/components/Position.hpp"

    namespace rtype
    {
        class RenderWindow
        {
            public:

                /**
                 * @brief Renders all displayable entities to the game window.
                 * @param components_array The array of ECS components.
                 */
                void render(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    static sf::Clock clock;
                    float deltaTime = clock.restart().asSeconds();

                    try {
                        auto &displayable = std::any_cast<ecs::SparseArray<Displayable> &>(components_array.at(typeid(Displayable)));
                        auto &windows = std::any_cast<ecs::SparseArray<Window> &>(components_array.at(typeid(Window)));
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array.at(typeid(ecs::Position)));
                        auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(components_array.at(typeid(Shader)));

                        auto lawindow = windows[0].value().getRenderWindow().get();
                        auto leshader = shader[0].value().getShader().get();
                        lawindow->clear(sf::Color::Yellow);
                        for (size_t i = 0; i < displayable.size(); ++i) {
                            if (displayable[i].has_value() && positions[i].has_value()) {
                                displayable[i].value().update(deltaTime);
                                displayable[i].value().setSpritePosition(positions[i].value()._pos_x, positions[i].value()._pos_y);
                                lawindow->draw(*displayable[i].value().getSprite(), leshader);
                                std::cout << "RENDER : " << i << std::endl;
                            }
                        }
                        lawindow->display();
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

                /**
                 * @brief Changes the background sprite to a new one.
                 * @param components_array The array of ECS components.
                 * @param sprite The background sprite ID.
                 */
                void changeBackground(std::unordered_map<std::type_index, std::any> &components_array, SPRITES sprite)
                {
                    try {
                        auto &displayable = std::any_cast<ecs::SparseArray<Displayable> &>(components_array.at(typeid(Displayable)));

                        if (displayable[0].has_value()) {
                            displayable[0].value().setSprite(sprite);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

                /**
                 * @brief Moves the background by adjusting its position based on velocity.
                 * @param components_array The array of ECS components.
                 * @param menu Whether the game is in menu mode (background does not move).
                 */
                void move_background(std::unordered_map<std::type_index, std::any> &components_array, bool menu)
                {
                    if (menu)
                        return;
                    auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array.at(typeid(ecs::Position)));
                    auto &velocity = std::any_cast<ecs::SparseArray<ecs::Velocity> &>(components_array.at(typeid(ecs::Velocity)));

                    if (positions[0].has_value() && velocity[0].has_value())
                    {
                        if (positions[0].value()._pos_x <= -1920) {
                            positions[0].value()._pos_x = 0;
                        } else {
                            positions[0].value()._pos_x -= velocity[0].value().velocity;
                        }
                    }
                }

            private:
        };
    }

#endif /* !RENDERWINDOW_HPP_ */