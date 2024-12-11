#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

namespace rtype
{

    class Background
    {
    public:
        Background(const std::string &texturePath, int x, int y)
        {
            try
            {
                texture = std::make_shared<sf::Texture>();
                if (!texture->loadFromFile(texturePath))
                {
                    throw std::runtime_error("Failed to load texture from: " + texturePath);
                }
                std::cout << "[INFO] Texture loaded successfully from: " << texturePath
                          << " (Size: " << texture->getSize().x << "x" << texture->getSize().y << ")" << std::endl;

                sprite.setTexture(*texture);
                sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
                std::cout << "[INFO] Sprite initialized at position: (" << x << ", " << y << ")" << std::endl;
            }
            catch (const std::exception &e)
            {
                std::cerr << "[ERROR] " << e.what() << std::endl;
                throw;
            }
        }

        sf::Sprite &getSprite() { return sprite; }

    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
    };

}

#endif /* BACKGROUND_HPP_ */
