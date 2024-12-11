#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>

namespace rtype {

    class Background {
    public:
        Background(const std::string& texturePath, int x, int y) {
            try {
                if (!texture.loadFromFile(texturePath)) {
                    throw std::runtime_error("Failed to load background texture from: " + texturePath);
                }
                std::cout << "Texture loaded successfully from: " << texturePath << std::endl;
                sprite.setTexture(texture);
                sprite.setPosition(1,1);
                // sprite.setScale(x,y);
                // auto textureSize = texture.getSize();
                // sprite.setScale(
                //     static_cast<float>(x) / textureSize.x,
                //     static_cast<float>(y) / textureSize.y
                // );
                // sf::Vector2u textureSize = texture.getSize();
                // sprite.setScale(
                //     static_cast<float>(x) / textureSize.x,
                //     static_cast<float>(y) / textureSize.y
                // );
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
                throw; // Re-throw the exception after logging it
            }
        }

        sf::Sprite& getSprite() { return sprite; }

    private:
        sf::Texture texture;
        sf::Sprite sprite;
    };

}

#endif /* BACKGROUND_HPP_ */




// /*
// ** EPITECH PROJECT, 2024
// ** R-Type
// ** File description:
// ** Background
// */

// #ifndef BACKGROUND_HPP_
//     #define BACKGROUND_HPP_

//     #include <SFML/Graphics.hpp>
//     #include <memory>
//     #include <string>

//     namespace rtype
//     {
//         class Background
//         {
//         public:
//             Background(const std::string& texturePath, float width, float height)
//             {
//                 // Charger la texture depuis le fichier
//                 if (!texture.loadFromFile(texturePath)) {
//                     throw std::runtime_error("Failed to load background texture from: " + texturePath);
//                 }

//                 // Configurer le sprite
//                 sprite.setTexture(texture);

//                 // Redimensionner le sprite pour couvrir toute la fenêtre
//                 float scaleX = width / static_cast<float>(texture.getSize().x);
//                 float scaleY = height / static_cast<float>(texture.getSize().y);
//                 sprite.setScale(scaleX, scaleY);
//             }

//             ~Background() {}

//             // Récupérer le sprite pour le dessiner
//             const sf::Sprite& getSprite() const
//             {
//                 return sprite;
//             }

//             // Mettre à jour la texture si nécessaire
//             void updateTexture(const std::string& newTexturePath)
//             {
//                 if (!texture.loadFromFile(newTexturePath)) {
//                     throw std::runtime_error("Failed to load background texture from: " + newTexturePath);
//                 }
//                 sprite.setTexture(texture, true);
//             }

//         private:
//             sf::Texture texture;      // Texture utilisée pour le background
//             sf::Sprite sprite;        // Sprite associé à la texture
//         };
//     }

// #endif /* !BACKGROUND_HPP_ */
