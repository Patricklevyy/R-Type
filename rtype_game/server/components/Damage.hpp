/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Damage
*/

#ifndef DAMAGE_HPP_
    #define DAMAGE_HPP_

    namespace rtype
    {
        class Damage {
            public:
                Damage(int damages = 20) : _damages(damages) {}
                ~Damage() {}

                int _damages;

            protected:
            private:
        };
    }

#endif /* !DAMAGE_HPP_ */
