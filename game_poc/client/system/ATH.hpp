/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ATH
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
    #include "../components/TempDisplay.hpp"

    namespace poc_game
    {
        /**
         * @class ATH
         * @brief Class responsible for managing the in-game HUD elements.
         */
        class ATH {
            public:
                /**
                 * @brief Default constructor for ATH class.
                 */
                ATH() {}

                /**
                 * @brief Default destructor for ATH class.
                 */
                ~ATH() {}

                /**
                 * @brief Get the current mouse position in the game window.
                 * @param components_array The array containing the ECS components.
                 * @return sf::Vector2f The mouse position in the game world coordinates.
                 */
                sf::Vector2f getMousePosition(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &windows = std::any_cast<ecs::SparseArray<Window> &>(components_array.at(typeid(Window)));

                    auto lawindow = windows[0].value().getRenderWindow().get();
                    sf::Vector2i mousePosPixel = sf::Mouse::getPosition(*lawindow);
                    return lawindow->mapPixelToCoords(mousePosPixel);
                }

                /**
                 * @brief Remove the Play buttons from the display.
                 * @param ecs The ECS object containing all components.
                 * @return A list of removed button's indexes.
                 */
                std::list<size_t> removePlayButtons(ecs::ECS &ecs)
                {
                    auto &tempDisplays = std::any_cast<ecs::SparseArray<TempDisplay> &>(ecs._components_arrays.at(typeid(TempDisplay)));

                    std::list<size_t> deads;

                    for (std::size_t i = 0; i < tempDisplays.size(); ++i) {
                        if (tempDisplays[i].has_value()) {
                            deads.push_front(i);
                        }
                    }
                    return deads;
                }

                /**
                 * @brief Check if a level button was clicked.
                 * @param components_array The array containing the ECS components.
                 * @return A pair indicating if a level was clicked and the level itself.
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
                            if (positions[i].has_value() && displayables[i].has_value() && levels[i].has_value()) {
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
                        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
                        return std::make_pair(false, LEVELS{});
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                        return std::make_pair(false, LEVELS{});
                    }
                }

                /**
                 * @brief Check if the Play button was clicked.
                 * @param components_array The array containing the ECS components.
                 * @return bool True if the play button was clicked, or false.
                 */
                bool isPlayButtonClicked(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    try {
                        auto &tempdisplays = std::any_cast<ecs::SparseArray<TempDisplay> &>(components_array.at(typeid(TempDisplay)));
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(components_array.at(typeid(ecs::Position)));
                        auto &displayables = std::any_cast<ecs::SparseArray<Displayable> &>(components_array.at(typeid(Displayable)));

                        sf::Vector2f mousePos = getMousePosition(components_array);

                        float mouseX = mousePos.x;
                        float mouseY = mousePos.y;

                        for (std::size_t i = 0; i < positions.size(); ++i) {
                            if (positions[i].has_value() && displayables[i].has_value() && tempdisplays[i].has_value()) {
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
