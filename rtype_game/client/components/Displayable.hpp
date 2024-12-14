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
        Displayable(int sprite_id, float x, float y) {
            sprite = SpriteFactory::createSprite(sprite_id);

            sprite->setPosition(x, y);
        }

        std::shared_ptr<sf::Sprite> getSprite()
        {
            return sprite;
        }

        void setSpritePosition(float x, float y) {
            sprite->setPosition(x, y);
        }

    private:
        std::shared_ptr<sf::Sprite> sprite;
    };

}

#endif /* DISPLAYABLE_HPP_ */
