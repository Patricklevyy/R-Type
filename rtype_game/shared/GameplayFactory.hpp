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

        void init(const std::string& filename) {
            libconfig::Config cfg;

            try {
                cfg.readFile(filename.c_str());
            } catch (const libconfig::FileIOException& fioex) {
                std::cerr << "I/O error while reading file." << std::endl;
                throw;
            } catch (const libconfig::ParseException& pex) {
                std::cerr << "Parse error at " << pex.getFile() << ":" << pex.getLine()
                          << " - " << pex.getError() << std::endl;
                throw;
            }

            const libconfig::Setting& root = cfg.getRoot();

            const libconfig::Setting& playerSettings = root["gameplay"]["players"];
            int playerHealth, playerVelocity, playerDamage;
            playerSettings.lookupValue("health", playerHealth);
            playerSettings.lookupValue("velocity", playerVelocity);
            playerSettings.lookupValue("damage", playerDamage);

            player = std::make_tuple(playerHealth, playerVelocity, playerDamage);

            const libconfig::Setting& monsterSettings = root["gameplay"]["monsters"];
            for (int i = 0; i < monsterSettings.getLength(); ++i) {
                const libconfig::Setting& monster = monsterSettings[i];
                int health, velocity, damage;

                monster.lookupValue("health", health);
                monster.lookupValue("velocity", velocity);
                monster.lookupValue("damage", damage);

                monsters[i + 1] = std::make_tuple(health, velocity, damage);
            }

            const libconfig::Setting& bossSettings = root["gameplay"]["bosses"];
            for (int i = 0; i < bossSettings.getLength(); ++i) {
                const libconfig::Setting& boss = bossSettings[i];
                int health, velocity, damage;

                boss.lookupValue("health", health);
                boss.lookupValue("velocity", velocity);
                boss.lookupValue("damage", damage);

                bosses[i + SIMPLE_BOSS] = std::make_tuple(health, velocity, damage);
            }


            const libconfig::Setting& levelsSettings = root["gameplay"]["levels"];
            for (int i = 0; i < levelsSettings.getLength(); ++i) {
                const libconfig::Setting& level = levelsSettings[i];
                std::list<int> ids;

                for (int j = 0; j < level.getLength(); ++j) {
                    int id = level[j];
                    ids.push_back(id);
                }
                levels[i + 1] = ids;
            }

            const libconfig::Setting& asteroidSettings = root["gameplay"]["asteroides"];
            int spawningTime, number;
            asteroidSettings.lookupValue("spwaningTime", spawningTime);
            asteroidSettings.lookupValue("number", number);

            asteroids = std::make_pair(spawningTime, number);

            const libconfig::Setting& backgroundSettings = root["display"];
            int speed;
            backgroundSettings.lookupValue("background_speed", speed);

            background_speed = speed;
        }

        int getPlayerVelocity() {
            return std::get<1>(player);
        }

        int getPlayerHealth() {
            return std::get<0>(player);
        }

        int getPlayerPlayerDamage() {
            return std::get<2>(player);
        }

        void changeDifficulty(DIFFICULTY dif) {
            if (_difficulty == dif) {
                return;
            } else {
                _difficulty = dif;
                changeGameplayDifficulty();
            }
        }

        void changeGameplayDifficulty() {
            switch (_difficulty)
            {
                case DIFFICULTY::EASY:
                    std::get<1>(player) = 40;
                    break;
                case DIFFICULTY::MEDIUM:
                    std::get<1>(player) = 500;
                    break;
                case DIFFICULTY::HARD:
                    std::get<1>(player) = 1000;
                    break;
                default:
                    break;
            }
        }

        int getMonsterVelocity(SPRITES id) {
            return std::get<1>(monsters[id]);
        }

        int getMonsterHealth(SPRITES id) {
            return std::get<0>(monsters[id]);
        }

        int getMonsterDamage(SPRITES id) {
            return std::get<2>(monsters[id]);
        }

        int getBossVelocity(SPRITES id) {
            return std::get<1>(bosses[id]);
        }

        int getBossHealth(SPRITES id) {
            return std::get<0>(bosses[id]);
        }

        int getBossDamage(SPRITES id) {
            return std::get<2>(bosses[id]);
        }

        std::pair<int, int> getMonsterLevelSpawn(int level) {
            std::list<int> levelMonsters = levels[level];
            return std::make_pair(levelMonsters.front(), levelMonsters.back());
        }

        std::pair<int, int> getBossLevelSpawn() {
            return std::make_pair(SIMPLE_BOSS, SIMPLE_BOSS);
        }

        DIFFICULTY getDifficulty() {
            return _difficulty;
        }

        int getAsteroidsSpawnInterval() {
            return asteroids.first;
        }

        int getAsteroidsNumberOfSpawn() {
            return asteroids.second;
        }

        int getProjectilesHealth(SPRITES sprite) {
            switch (sprite)
            {
                case SPRITES::ASTEROIDE:
                    return 10000;
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

        int getProjectilesVelocity(SPRITES sprite) {
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

        int getProjectilesDamage(SPRITES sprite) {
            switch (sprite)
            {
            case PLAYER_SIMPLE_MISSILE:
                return getPlayerPlayerDamage();
            case PLAYER_CHARGED_SHOOT:
                return (getPlayerPlayerDamage() * 3);
            case MONSTER_SIMPLE_MISSILE:
                return getMonsterDamage(SPRITES::SIMPLE_MONSTER);
            case MONSTER_MULTIPLE_MISSILE:
                return getMonsterDamage(SPRITES::ADVANCED_MONSTER);
            case BABY_PROJECTILE:
                return getMonsterDamage(SPRITES::BABY_PROJECTILE);
            case FIRE_BALL:
                return getMonsterDamage(SPRITES::MEGA_MONSTER);
            case ASTEROIDE:
                return 20;
            default:
                std::cerr << "Monster Id not found" << std::endl;
                return 0;
            }
        }

        int getMonsterBodyDamage(SPRITES sprite) {
            switch (sprite)
            {
            case SPRITES::SIMPLE_MONSTER:
                return 20;
            case SPRITES::ADVANCED_MONSTER:
                return 30;
            case SPRITES::BABY_PROJECTILE:
                return 20;
            case SPRITES::MEGA_MONSTER:
                return 50;
            case SPRITES::SIMPLE_BOSS:
                return 500;
            default:
                return 0;
            }
        }

        int getMonsterScoreValue(SPRITES sprite) {
            switch (sprite)
            {
            case SPRITES::SIMPLE_BOSS:
                return 100;
            default:
                return 1;
            }
        }

        int getPlayerBodyDamage() {
            return 20;
        }

        float getBackgroundSpeed() {
            return background_speed;
        }

    protected:
    private:
        std::map<int, std::tuple<int, int, int>> monsters;
        std::map<int, std::tuple<int, int, int>> bosses;
        std::map<int, std::list<int>> levels;
        std::tuple<int, int, int> player;
        std::pair<int, int> asteroids;
        float background_speed = 0;

        DIFFICULTY _difficulty = EASY;
    };
}

#endif /* !GAMEPLAYFACTORY_HPP_ */
