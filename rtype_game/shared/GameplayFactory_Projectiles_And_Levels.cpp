/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameplayFactory_Projectiles_And_Levels
*/

#include "GameplayFactory.hpp"

namespace rtype
{
    void GameplayFactory::changeDifficulty(DIFFICULTY dif) {
            if (_difficulty == dif) {
                return;
            } else {
                _difficulty = dif;
                changeGameplayDifficulty();
            }
        }

        void GameplayFactory::changeGameplayDifficulty() {
            switch (_difficulty) {
                case DIFFICULTY::EASY:
                    break;

                case DIFFICULTY::MEDIUM:
                    std::get<0>(player) = std::get<0>(player) * 0.67;
                    std::get<1>(player) = std::get<1>(player) * 0.83;
                    std::get<2>(player) = std::get<2>(player) * 0.67;

                    for (auto& monster : monsters) {
                        std::get<0>(monster.second) *= 1.25;
                        std::get<1>(monster.second) *= 1.2;
                        std::get<2>(monster.second) *= 1.33;
                    }

                    for (auto& boss : bosses) {
                        std::get<0>(boss.second) *= 1.25;
                        std::get<1>(boss.second) *= 1.25;
                        std::get<2>(boss.second) *= 1.33;
                    }

                    asteroids.first *= 0.71;
                    asteroids.second = 4;

                    background_speed *= 1.25;
                    break;

                case DIFFICULTY::HARD:
                    std::get<0>(player) = std::get<0>(player) * 0.53;
                    std::get<1>(player) = std::get<1>(player) * 0.75;
                    std::get<2>(player) = std::get<2>(player) * 0.53;

                    for (auto& monster : monsters) {
                        std::get<0>(monster.second) *= 1.625;
                        std::get<1>(monster.second) *= 1.4;
                        std::get<2>(monster.second) *= 1.67;
                    }

                    for (auto& boss : bosses) {
                        std::get<0>(boss.second) *= 1.5;
                        std::get<1>(boss.second) *= 1.5;
                        std::get<2>(boss.second) *= 2.0;
                    }

                    asteroids.first *= 0.50;
                    asteroids.second = 5;

                    background_speed *= 1.5;
                    break;
            }
        }

        DIFFICULTY GameplayFactory::getDifficulty() {
            return _difficulty;
        }

        int GameplayFactory::getAsteroidsSpawnInterval() {
            return asteroids.first;
        }

        int GameplayFactory::getAsteroidsNumberOfSpawn() {
            return asteroids.second;
        }

        int GameplayFactory::getProjectilesHealth(SPRITES sprite) {
            switch (sprite)
            {
                case SPRITES::ASTEROIDE:
                    return 1000;
                case SPRITES::PLAYER_SIMPLE_MISSILE:
                    return 10;
                case SPRITES::PLAYER_CHARGED_SHOOT:
                    return 50;
                case SPRITES::MONSTER_MULTIPLE_MISSILE:
                    return 10;
                case SPRITES::BABY_PROJECTILE:
                    return 60;
                case SPRITES::FIRE_BALL:
                    return 10;
                case SPRITES::MONSTER_SIMPLE_MISSILE:
                    return 10;
                default:
                    std::cerr << "Id of this projectilesss not found : "<< sprite << std::endl;
                    return 0;
            }
        }

        int GameplayFactory::getProjectilesVelocity(SPRITES sprite) {
            switch (sprite)
            {
            case BABY_PROJECTILE:
                return 200;
            case PLAYER_CHARGED_SHOOT:
                return 400;
            default:
                return 300;
            }
        }


        float GameplayFactory::getBackgroundSpeed() {
            return background_speed;
        }
}