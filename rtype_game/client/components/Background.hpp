#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

namespace rtype {

    class Background {
    public:
        Background(std::shared_ptr<sf::Texture> texturePtr, int x, int y) 
            : texture(texturePtr)
        {
            if (!texture) {
                throw std::runtime_error("Invalid texture pointer!");
            }
            sprite.setTexture(*texture);
            sprite.setPosition(static_cast<float>(x), static_cast<float>(y));
            std::cout << "[INFO] Background initialized at position: (" << x << ", " << y << ")" << std::endl;
        }

        sf::Sprite& getSprite() { return sprite; }

        std::shared_ptr<sf::Texture> getTexture() const { return texture; }
        

    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
    };

}

#endif /* BACKGROUND_HPP_ */
