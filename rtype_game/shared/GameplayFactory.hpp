/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameplayFactory
*/

#ifndef GAMEPLAYFACTORY_HPP_
#define GAMEPLAYFACTORY_HPP_

#include <libconfig.h++>
#include <iostream>
#include <map>
#include <list>
#include <tuple>
#include <string>
#include "Enums.hpp"

namespace rtype {
    class GameplayFactory {
    public:
        GameplayFactory() {}
        ~GameplayFactory() {}

        void init(const std::string&);

        BONUS getRandomBonuses(int);

        SPRITES getSpriteBonus(BONUS);

        int getBonusSpeed() const;

        int getShieldDuration();

        int getLifeBonus();

        int getVelocityDurationBonus();

        int getVelocityBoostBonus();

        int getPlayerVelocity();

        int getPlayerHealth();

        int getPlayerPlayerDamage();

        int getMonsterVelocity(SPRITES);

        int getMonsterHealth(SPRITES);

        int getMonsterDamage(SPRITES);

        int getBossVelocity(SPRITES);

        int getBossHealth(SPRITES);

        int getBossDamage(SPRITES);

        int getMonsterBodyDamage(SPRITES);

        int getProjectilesDamage(SPRITES);

        int getMonsterScoreValue(SPRITES);

        int getPlayerBodyDamage();

        std::pair<int, int> getMonsterLevelSpawn(int);

        std::pair<int, int> getBossLevelSpawn();

        void changeDifficulty(DIFFICULTY);

        void changeGameplayDifficulty();

        DIFFICULTY getDifficulty();

        int getAsteroidsSpawnInterval();

        int getAsteroidsNumberOfSpawn();

        int getProjectilesHealth(SPRITES);

        int getProjectilesVelocity(SPRITES);

        float getBackgroundSpeed();

    protected:
    private:
        std::map<int, std::tuple<int, int, int>> monsters;
        std::map<int, std::tuple<int, int, int>> bosses;
        std::map<int, std::list<int>> levels;
        std::tuple<int, int, int> player;
        std::pair<int, int> asteroids;
        std::map<int, std::pair<int, int>> bonuses;
        int bonus_speed = 0;
        float background_speed = 0;

        DIFFICULTY _difficulty = EASY;
    };
}

#endif /* !GAMEPLAYFACTORY_HPP_ */
