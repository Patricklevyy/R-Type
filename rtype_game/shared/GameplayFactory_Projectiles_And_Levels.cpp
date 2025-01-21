/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameplayFactory_Projectiles_And_Levels
*/

#include "GameplayFactory.hpp"

namespace rtype
{
    void GameplayFactory::changeDifficulty(DIFFICULTY dif)
    {
        if (_difficulty == dif) {
            return;
        } else {
            _difficulty = dif;
            changeGameplayDifficulty();
        }
    }

    void GameplayFactory::changeGameplayDifficulty()
    {
        if (_difficulty == DIFFICULTY::MEDIUM) {
            std::get<0>(player) = std::get<0>(player) * 0.67;

            for (auto &monster : monsters) {
                std::get<0>(monster.second) *= 1.25;
                std::get<1>(monster.second) *= 1.2;
                std::get<2>(monster.second) *= 1.33;
            }

            for (auto &boss : bosses) {
                std::get<0>(boss.second) *= 1.25;
                std::get<1>(boss.second) *= 1.25;
                std::get<2>(boss.second) *= 1.33;
            }

            std::get<0>(asteroids) *= 0.71;
            std::get<1>(asteroids) = 4;

            background_speed *= 1.25;
        } else if (_difficulty == DIFFICULTY::HARD
            || _difficulty == DIFFICULTY::IMPOSSIBLE) {
            std::get<0>(player) = std::get<0>(player) * 0.53;

            for (auto &monster : monsters) {
                std::get<0>(monster.second) *= 1.625;
                std::get<1>(monster.second) *= 1.4;
                std::get<2>(monster.second) *= 1.67;
            }

            for (auto &boss : bosses) {
                std::get<0>(boss.second) *= 1.5;
                std::get<1>(boss.second) *= 1.5;
                std::get<2>(boss.second) *= 2.0;
            }

            std::get<0>(asteroids) *= 0.50;
            std::get<1>(asteroids) = 5;

            background_speed *= 1.5;
        }
    }

    DIFFICULTY GameplayFactory::getDifficulty()
    {
        return _difficulty;
    }

    int GameplayFactory::getAsteroidsSpawnInterval()
    {
        return std::get<0>(asteroids);
    }

    int GameplayFactory::getAsteroidsNumberOfSpawn()
    {
        return std::get<1>(asteroids);
    }

    int GameplayFactory::getProjectilesHealth(SPRITES sprite)
    {
        switch (sprite) {
            case SPRITES::ASTEROIDE: return 1000;
            case SPRITES::PLAYER_SIMPLE_MISSILE: return 10;
            case SPRITES::PLAYER_RED_MISSILE: return 50;
            case SPRITES::PLAYER_CHARGED_SHOOT: return 200;
            case SPRITES::PLAYER_RED_CHARGED_SHOOT: return 100;
            case SPRITES::MONSTER_MULTIPLE_MISSILE: return 10;
            case SPRITES::BABY_PROJECTILE: return 60;
            case SPRITES::FIRE_BALL: return 10;
            case SPRITES::MONSTER_SIMPLE_MISSILE: return 10;
            case SPRITES::BOSS_PROJECTILE: return 1000;
            default:
                std::cerr << "Id of this projectilesss not found : " << sprite
                          << std::endl;
                return 0;
        }
    }

    int GameplayFactory::getProjectilesVelocity(SPRITES sprite)
    {
        switch (sprite) {
            case BABY_PROJECTILE: return 200;
            case PLAYER_CHARGED_SHOOT: return 400;
            case PLAYER_RED_MISSILE: return 700;
            case PLAYER_RED_CHARGED_SHOOT: return 1000;
            default: return 300;
        }
    }

    float GameplayFactory::getBackgroundSpeed()
    {
        return background_speed;
    }
} // namespace rtype