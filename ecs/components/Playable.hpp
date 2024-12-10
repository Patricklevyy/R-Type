/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Playable
*/

#ifndef PLAYABLE_HPP_
    #define PLAYABLE_HPP_

    namespace ecs
    {
        class Playable
        {
        public:
            Playable(std::string name = "") : _name(name) {}
            ~Playable() {}

            std::string _name;

        protected:
        private:
        };
    }

#endif /* !PLAYABLE_HPP_ */