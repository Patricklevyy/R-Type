/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
    #define VELOCITY_HPP_

    namespace ecs
    {
        class Velocity
        {
        public:
            Velocity() {}
            ~Velocity() {}

            float velocity = 10.0; // PEUT ETRE CE SERAI BIEN DE POUVOIR LE SET DANS UN FICHIER DE CONFIG DE JEU ?

        protected:
        private:
        };
    }

#endif /* !VELOCITY_HPP_ */
