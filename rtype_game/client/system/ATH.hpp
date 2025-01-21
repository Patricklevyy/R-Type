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

    namespace rtype
    {
      /**
       * @class ATH
       * @brief Handles animations and interactions in the game, including level management and mouse input detection.
       */
        class ATH {
            public:
                /**
                 * @brief Default constructor for the ATH class.
                 */
                ATH() {}

                /**
                 * @brief Default destructor for the ATH class.
                 */
                ~ATH() {}

                /**
                 * @brief Retrieves the mouse position in world coordinates relative to the render window.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @return A 2D vector representing the mouse position in world coordinates.
                 */
                sf::Vector2f getMousePosition(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    auto &windows = std::any_cast<ecs::SparseArray<Window> &>(components_array.at(typeid(Window)));

                    auto lawindow = windows[0].value().getRenderWindow().get();
                    sf::Vector2i mousePosPixel = sf::Mouse::getPosition(*lawindow);
                    return lawindow->mapPixelToCoords(mousePosPixel);
                }

                /**
                 * @brief Removes all level entities from the ECS.
                 * @param ecs A reference to the ECS instance managing the game entities and components.
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
                 * @brief Checks if a level entity has been clicked by the user.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @return A pair containing a boolean and a LEVELS value.
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
                 * @brief Checks if a win or lose entity has been clicked by the user.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @return true if a win or lose entity is clicked, false otherwise.
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
