/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

    namespace rtype
    {
        class SpriteId {
            public:
                SpriteId(int sprite) : _sprite(sprite) {}
                ~SpriteId() {}

                int _sprite;
            protected:
            private:
        };
    }

#endif /* !SPRITE_HPP_ */
