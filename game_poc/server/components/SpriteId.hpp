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

#ifndef SPRITEID_HPP_
    #define SPRITEID_HPP_

    namespace poc_game
    {
        /**
         * @class SpriteId
         * @brief A class that handles SpritesId for entity in the game.
         */
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

#endif /* !SPRITEID_HPP_ */
