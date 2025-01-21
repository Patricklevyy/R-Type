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
        /**
         * @class Damage
         * @brief A class that handles damage of entities.
         */
        class Damage {
            public:
                /**
                 * @brief Constructor for the Damage class.
                 */
                Damage(int damages = 20) : _damages(damages) {}

                /**
                 * @brief Destructor for the Damage class.
                 */
                ~Damage() {}

                int _damages;

            protected:
            private:
        };
    }

#endif /* !DAMAGE_HPP_ */
