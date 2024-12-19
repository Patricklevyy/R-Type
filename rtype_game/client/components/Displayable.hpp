#ifndef DISPLAYABLE_HPP_
#define DISPLAYABLE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <string>
#include "../SpriteFactory.hpp"

namespace rtype {

    class Displayable {
    public:
        Displayable(SPRITES sprite_id)
            : currentFrame(0), elapsedTime(0.0f)
        {
            textures = SpriteFactory::loadTexturesForSprite(sprite_id);
            std::tuple<float, float, float> scales_and_speed = SpriteFactory::getSpriteScaleAndSpeed(sprite_id);

            animationSpeed = std::get<2>(scales_and_speed);
            if (textures.empty()) {
                throw std::runtime_error("No textures available for sprite ID");
            }
            sprite = std::make_shared<sf::Sprite>();
            sprite->setTexture(*textures[currentFrame]);
            sprite->setScale(std::get<0>(scales_and_speed), std::get<1>(scales_and_speed));
        }

         void update(float deltaTime) {
            elapsedTime += deltaTime;
            if (elapsedTime >= animationSpeed) {
                elapsedTime = 0.0f;
                currentFrame = (currentFrame + 1) % textures.size();
                sprite->setTexture(*textures[currentFrame]);
            }
        }

        std::shared_ptr<sf::Sprite> getSprite()
        {
            return sprite;
        }

        void setSpritePosition(float x, float y) {
            sprite->setPosition(x, y);
        }

        void setSprite(SPRITES new_sprite_id) {
            sprite.reset();
            currentFrame = 0;
            textures = SpriteFactory::loadTexturesForSprite(new_sprite_id);
            std::tuple<float, float, float> scales_and_speed = SpriteFactory::getSpriteScaleAndSpeed(new_sprite_id);

            animationSpeed = std::get<2>(scales_and_speed);

            if (textures.empty()) {
                throw std::runtime_error("No textures available for sprite ID");
            }

            sprite = std::make_shared<sf::Sprite>();
            sprite->setTexture(*textures[currentFrame]);
            sprite->setScale(std::get<0>(scales_and_speed), std::get<1>(scales_and_speed));
        }

    private:
        std::shared_ptr<sf::Sprite> sprite;
        std::vector<std::shared_ptr<sf::Texture>> textures;
        size_t currentFrame;
        float animationSpeed;
        float elapsedTime;
    };

}

#endif /* DISPLAYABLE_HPP_ */
