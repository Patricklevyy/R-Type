#ifndef RENDERWINDOW_HPP_
    #define RENDERWINDOW_HPP_

    #include "../components/Window.hpp"
    #include "../components/Background.hpp"
    #include "../../shared/Includes.hpp"
    #include <iostream>
    #include "../../../ecs/SparseArray.hpp"

    namespace rtype
    {
        class RenderWindow
        {
            public:

                void render(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    try {
                        // Récupération des composants
                        auto &windows = std::any_cast<ecs::SparseArray<Window> &>(components_array.at(typeid(Window)));
                        auto &backgrounds = std::any_cast<ecs::SparseArray<Background> &>(components_array.at(typeid(Background)));

                        std::cout << "[INFO] Composants récupérés avec succès." << std::endl;

                        for (size_t i = 0; i < windows.size(); ++i) {
                            if (!windows[i] || !backgrounds[i]) {
                                std::cerr << "[WARNING] Missing component for entity " << i << std::endl;
                                continue;
                            }

                            auto& window = windows[i].value();
                            auto& background = backgrounds[i].value();
                            auto renderWindow = window.getRenderWindow();

                            // Vérification de la fenêtre
                            if (!renderWindow) {
                                std::cerr << "[ERROR] RenderWindow is null for entity " << i << std::endl;
                                continue;
                            }

                            renderWindow->clear(sf::Color::Black);

                            // Vérification du sprite avant affichage
                            auto& sprite = background.getSprite();
                            sf::FloatRect bounds = sprite.getGlobalBounds();
                            std::cout << "[INFO] Rendering background for entity " << i
                                      << " at bounds: (" << bounds.left << ", " << bounds.top
                                      << ") - (" << bounds.width << "x" << bounds.height << ")" << std::endl;
            
                            renderWindow->draw(sprite);
                            renderWindow->display();

                            std::cout << "[INFO] Rendu terminé pour l'entité " << i << std::endl;
                        }
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
