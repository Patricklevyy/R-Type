/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

namespace rtype {

    class Health {
        public:
            Health(int health) : _health(health){};
            ~Health() {};

            int _health;

        protected:
        private:
    };
}

#endif /* !HEALTH_HPP_ */
