#ifndef DISPLAYABLE_HPP_
#define DISPLAYABLE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>

namespace ecs {

    class Displayable {
    public:
        Displayable(const std::string &texturePath, int x, int y) {
            try {
                texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile(texturePath)) {
                    throw std::runtime_error("Failed to load texture from: " + texturePath);
                }
                sprite.setTexture(*texture);
                sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
                std::cout << "[INFO] Displayable initialized with texture: " << texturePath << " at position (" << x << ", " << y << ")" << std::endl;
            } catch (const std::exception &e) {
                std::cerr << "[ERROR] " << e.what() << std::endl;
                throw;
            }
        }

        sf::Sprite &getSprite()
        {
            return sprite;
        }

        void setSpritePosition(float x, float y) {
            sprite.setPosition(x, y);
        }

    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
    };

}

#endif /* DISPLAYABLE_HPP_ */
