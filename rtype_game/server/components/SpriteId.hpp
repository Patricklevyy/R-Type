/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Sprite
*/

#ifndef SPRITEID_HPP_
    #define SPRITEID_HPP_

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

#endif /* !SPRITEID_HPP_ */
