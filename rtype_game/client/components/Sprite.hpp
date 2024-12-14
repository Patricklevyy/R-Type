#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

namespace rtype {

    class Sprite {
    public:
        Sprite() = default;

        Sprite(const std::string& texturePath, float width, float height) {
            if (!texture->loadFromFile(texturePath)) {
                throw std::runtime_error("Failed to load texture: " + texturePath);
            }
            sprite.setTexture(*texture);
            sprite.setScale(width / texture->getSize().x, height / texture->getSize().y);
        }

        void setPosition(float x, float y)
        {
            sprite.setPosition(x, y);
        }

        sf::Vector2f getPosition() const
        {
            return sprite.getPosition();
        }

        void draw(sf::RenderWindow& window) const
        {
            window.draw(sprite);
        }

        void setRotation(float angle)
        {
            sprite.setRotation(angle);
        }

        float getRotation() const
        {
            return sprite.getRotation();
        }

    private:
        std::shared_ptr<sf::Texture> texture;
        sf::Sprite sprite;
    };
}

#endif /* SPRITE_HPP_ */
