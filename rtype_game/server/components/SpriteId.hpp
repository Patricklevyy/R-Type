/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

/**
 * @file SpriteId.hpp
 * @brief Class representing a sprite identifier.
 *
 * The SpriteId class is used to associate an entity with a specific sprite.
 */

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

    namespace rtype
    {
        class SpriteId {
            public:

                /**
                * @brief Constructor for the SpriteId class.
                * @param sprite The identifier for the sprite.
                */
                SpriteId(int sprite) : _sprite(sprite) {}

                /**
                * @brief Destructor for the SpriteId class.
                */
                ~SpriteId() {}

                int _sprite;
            protected:
            private:
        };
    }

#endif /* !SPRITE_HPP_ */
