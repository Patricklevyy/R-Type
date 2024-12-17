/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** HitboxFactory
*/

#ifndef HitboxFactory_HPP_
    #define HitboxFactory_HPP_

    #include "../shared/Includes.hpp"
    #include "../shared/Enums.hpp"

    namespace rtype
    {
        class HitboxFactory
            {
            public:
                static std::pair<int, int> createHitbox(SPRITES id)
                {
                    std::cout << "SPRITE ID =>>> " << id << std::endl;
                    int x;
                    int y;
                    switch (id)
                    {
                    case SPRITES::MY_PLAYER_SHIP:
                        x = 100;
                        y = 100; 
                        break;
                    case SPRITES::MONSTER:
                        x = 100;
                        y = 100; 
                        break;
                    case SPRITES::OTHER_PLAYER_SHIP:
                        x = 100;
                        y = 100; 
                        break;
                    case SPRITES::PLAYER_SIMPLE_MISSILE:
                        x = 100;
                        y = 100; 
                        break;
                    default:
                        throw std::invalid_argument("Invalid sprite ID");
                    }

                   std::pair<int, int> hitbox = std::make_pair(x, y);

                    return hitbox;
                }

            private:
        };

    }

#endif /* !HitboxFactory_HPP_ */
