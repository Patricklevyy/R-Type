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
    /**
     * @class GameplayFactory
     * @brief A class to manage the gameplay of the game.
     */
    class GameplayFactory {
    public:
        /**
         * @brief Constructor for the GameplayFactory class.
         */
        GameplayFactory() {}

        /**
         * @brief Destructor for the GameplayFactory class.
         */
        ~GameplayFactory() {}

        /**
         * @brief Init the game.
         * @param filename Take the config file as parameter.
         */
        void init(const std::string&);

        /**
         * @brief Generate one of the possible Bonuses.
         * @param enum Enum of the Bonus.
         */
        BONUS getRandomBonuses(int);

        /**
         * @brief Get the sprite of the possible Bonuses.
         * @param enum Enum of the Bonus.
         */
        SPRITES getSpriteBonus(BONUS);

        /**
         * @brief Get the speed of the Bonus.
         */
        int getBonusSpeed() const;

        /**
         * @brief Get the duration of the shield that is set in the config file.
         */
        int getShieldDuration();

        /**
         * @brief Get the life to add that is set in the config file.
         */
        int getLifeBonus();

        /**
         * @brief Get the speed duration that is set in the config file.
         */
        int getWeaponDurationBonus();

        /**
         * @brief Get the speed that is set in the config file.
         */
        int getWeaponBoostBonus();

        /**
         * @brief Get the speed duration that is set in the config file.
         */
        int getVelocityDurationBonus();

        /**
         * @brief Get the speed that is set in the config file.
         */
        int getVelocityBoostBonus();

        /**
         * @brief Get the speed of the player that is set in the config file.
         */
        int getPlayerVelocity();

        /**
         * @brief Get the health of the player that is set in the config file.
         */
        int getPlayerHealth();

        /**
         * @brief Get the damage of the player that is set in the config file.
         */
        int getPlayerPlayerDamage();

        /**
         * @brief Get the speed of the monsters by it type.
         * @param SPRITES The enum of the monster.
         */
        int getMonsterVelocity(SPRITES);

        /**
         * @brief Get the health of the monsters by it type.
         * @param SPRITES The enum of the monster.
         */
        int getMonsterHealth(SPRITES);

        /**
         * @brief Get the damage of the monsters by it type.
         * @param SPRITES The enum of the monster.
         */
        int getMonsterDamage(SPRITES);

        /**
         * @brief Get the speed of the Boss.
         * @param SPRITES The enum of the monster.
         */
        int getBossVelocity(SPRITES);

        /**
         * @brief Get the health of the Boss.
         * @param SPRITES The enum of the monster.
         */
        int getBossHealth(SPRITES);

        /**
         * @brief Get the damage of the Boss.
         * @param SPRITES The enum of the monster.
         */
        int getBossDamage(SPRITES);

        /**
         * @brief Get the damage of the body of the monsters.
         * @param SPRITES The enum of the monster.
         */
        int getMonsterBodyDamage(SPRITES);

        /**
         * @brief Get the damage of the projectile.
         * @param SPRITES The enum of the projectile.
         */
        int getProjectilesDamage(SPRITES);

        /**
         * @brief Get the value of the Monster when killed.
         * @param SPRITES The enum of the monster.
         */
        int getMonsterScoreValue(SPRITES);

        /**
         * @brief Get the damage of the player.
         */
        int getPlayerBodyDamage();

        /**
         * @brief Get the level When monster can appear.
         * @param int The enum of the monster.
         */
        std::pair<int, int> getMonsterLevelSpawn(int);

        /**
         * @brief Get the damage of the Boss.
         */
        std::pair<int, int> getBossLevelSpawn();

        /**
         * @brief Modify the difficulty of the game.
         * @param DIFFICULTY The enum of the difficulty.
         */
        void changeDifficulty(DIFFICULTY);

        /**
         * @brief Get the difficulty of the gameplay.
         */
        void changeGameplayDifficulty();

        /**
         * @brief Get the difficulty of the game.
         */
        DIFFICULTY getDifficulty();

        /**
         * @brief Get the interval time that is set between a spawn of an asteroid.
         */
        int getAsteroidsSpawnInterval();

        /**
         * @brief Get the number of asteroid that have been creates.
         */
        int getAsteroidsNumberOfSpawn();

        /**
         * @brief Get the health of the projectils.
         * @param SPRITES The enum of the projectile.
         */
        int getProjectilesHealth(SPRITES);

        /**
         * @brief Get the speed of the projectile.
         * @param SPRITES The enum of the projectile.
         */
        int getProjectilesVelocity(SPRITES);

        /**
         * @brief Get speed of the background that is set in the config file.
         */
        float getBackgroundSpeed();

    protected:
    private:
        std::map<int, std::tuple<int, int, int>> monsters;
        std::map<int, std::tuple<int, int, int>> bosses;
        std::map<int, std::list<int>> levels;
        std::tuple<int, int, int> player;
        std::tuple<int, int, int> asteroids;
        std::map<int, std::pair<int, int>> bonuses;
        int bonus_speed = 0;
        float background_speed = 0;

        DIFFICULTY _difficulty = EASY;
    };
}

#endif /* !GAMEPLAYFACTORY_HPP_ */
