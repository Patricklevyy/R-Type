/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ATH
*/

/**
 * @file ATH.hpp
 * @brief Header file for the ATH (Above The Health) class.
 *
 * This file contains the declaration of the ATH class, which provides methods for handling
 * various aspects of the game interface related to level selection, mouse interactions, 
 * and clearing components from the ECS.
 */

#ifndef ATH_HPP_
    #define ATH_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../shared/components/Levels.hpp"
    #include "../components/Displayable.hpp"
    #include "../components/Window.hpp"

    namespace rtype
    {
        /**
         * @class ATH
         * @brief A class that manages level interactions and mouse handling in the game.
         *
         * The ATH class provides methods for interacting with levels, handling mouse events
         * for level clicks, checking win/loss conditions, and removing certain ECS components
         * such as levels, health, and position.
         */
        class ATH {
            public:
                /**
                 * @brief Default constructor for the ATH class.
                 */
                ATH() {}
                /**
                 * @brief Destructor for the ATH class.
                 */
                ~ATH() {}

                /**
                 * @brief Get the mouse position in world coordinates.
                 *
                 * This method retrieves the current position of the mouse in the world coordinate
                 * system by accessing the render window and using the mouse position in pixels.
                 * The position is then converted to world coordinates.
                 * 
                 * @param components_array The array of components of entities in the ECS system.
                 * @return A vector representing the mouse position in world coordinates.
                 */
                sf::Vector2f getMousePosition(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &windows = std::any_cast<ecs::SparseArray<Window> &>(components_array.at(typeid(Window)));

                    auto lawindow = windows[0].value().getRenderWindow().get();
                    sf::Vector2i mousePosPixel = sf::Mouse::getPosition(*lawindow);
                    return lawindow->mapPixelToCoords(mousePosPixel);
                }

                /**
                 * @brief Removes all levels from the ECS system.
                 *
                 * This method loops through all the levels in the ECS system and removes associated
                 * components such as position, levels, and displayable components from the system.
                 * 
                 * @param ecs The ECS system containing the components to be removed.
                 */
                void removeLevels(ecs::ECS &ecs)
                {
                    auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(ecs._components_arrays.at(typeid(Levels)));

                    for (std::size_t i = 0; i < levels.size(); ++i) {
                        if (levels[i].has_value()) {
                            ecs.killEntityFromRegistry<ecs::Position>(i);
                            ecs.killEntityFromRegistry<Levels>(i);
                            ecs.killEntityFromRegistry<Displayable>(i);
                        }
                    }
                }

                /**
                 * @brief Checks if a level has been clicked by the user.
                 *
                 * This method checks if any level (represented by entities in the ECS) was clicked
                 * by checking the position of the mouse in comparison to the displayed levels.
                 * If a level is clicked, it returns the level that was clicked.
                 * 
                 * @param components_array The array of components of entities in the ECS system.
                 * @return A pair indicating whether a level was clicked and the level information.
                 */
                std::pair<bool, LEVELS> isLevelClicked(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    try {
                        auto &levels = std::any_cast<ecs::SparseArray<Levels> &>(components_array.at(typeid(Levels)));
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array.at(typeid(ecs::Position)));
                        auto &displayables = std::any_cast<ecs::SparseArray<Displayable> &>(components_array.at(typeid(Displayable)));

                        sf::Vector2f mousePos = getMousePosition(components_array);

                        float mouseX = mousePos.x;
                        float mouseY = mousePos.y;

                        for (std::size_t i = 0; i < positions.size(); ++i) {
                            if (positions[i].has_value() && i < displayables.size() && displayables[i].has_value() && i < levels.size() && levels[i].has_value()) {
                                auto size = displayables[i].value().getSpriteSize();

                                if (mouseX >= positions[i].value()._pos_x && mouseX <= positions[i].value()._pos_x + size.x &&
                                    mouseY >= positions[i].value()._pos_y && mouseY <= positions[i].value()._pos_y + size.y) {
                                    std::cout << "Entity clicked! Level: " << levels[i].value()._level << std::endl;
                                    return std::make_pair(true, levels[i].value()._level);
                                }
                            }
                        }
                        return std::make_pair(false, LEVELS{});
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCption] " << e.what() << std::endl;
                        return std::make_pair(false, LEVELS{});
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                        return std::make_pair(false, LEVELS{});
                    }
                }

                /**
                 * @brief Checks if a win or loss condition was clicked by the user.
                 *
                 * This method checks if the user clicked on any elements representing win or loss
                 * conditions by comparing the mouse position to the position and size of the elements.
                 * 
                 * @param components_array The array of components of entities in the ECS system.
                 * @return True if a win/loss condition was clicked, false otherwise.
                 */
                bool isLooseOrWinClicked(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    try {
                        auto &level_status = std::any_cast<ecs::SparseArray<LevelStatus> &>(components_array.at(typeid(LevelStatus)));
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array.at(typeid(ecs::Position)));
                        auto &displayables = std::any_cast<ecs::SparseArray<Displayable> &>(components_array.at(typeid(Displayable)));

                        sf::Vector2f mousePos = getMousePosition(components_array);

                        float mouseX = mousePos.x;
                        float mouseY = mousePos.y;

                        for (std::size_t i = 0; i < positions.size(); ++i) {
                            if (positions[i].has_value() && i < displayables.size() && displayables[i].has_value() && i < level_status.size() && level_status[i].has_value()) {
                                auto size = displayables[i].value().getSpriteSize();

                                if (mouseX >= positions[i].value()._pos_x && mouseX <= positions[i].value()._pos_x + size.x &&
                                    mouseY >= positions[i].value()._pos_y && mouseY <= positions[i].value()._pos_y + size.y) {
                                    return true;
                                }
                            }
                        }
                        return false;
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
                        return false;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                        return false;
                    }
                }

            protected:
            private:
        };
    }

#endif /* !ATH_HPP_ */
