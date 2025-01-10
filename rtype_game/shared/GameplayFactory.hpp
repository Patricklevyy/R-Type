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
        }

        void printConfig() const {
            std::cout << "Player Config:" << std::endl;
            std::cout << "  Health: " << std::get<0>(player) << std::endl;
            std::cout << "  Velocity: " << std::get<1>(player) << std::endl;
            std::cout << "  Damage: " << std::get<2>(player) << std::endl;

            std::cout << "Monster Configs:" << std::endl;
            for (const auto& [id, config] : monsters) {
                std::cout << "  Monster " << id << ":" << std::endl;
                std::cout << "    Health: " << std::get<0>(config) << std::endl;
                std::cout << "    Velocity: " << std::get<1>(config) << std::endl;
                std::cout << "    Damage: " << std::get<2>(config) << std::endl;
            }

            std::cout << "Levels Config:" << std::endl;
            for (const auto& [level, ids] : levels) {
                std::cout << "  Level " << level << ": ";
                for (int id : ids) {
                    std::cout << id << " ";
                }
                std::cout << std::endl;
            }
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
                    std::get<1>(player) = 0;
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

        std::pair<int, int> getLevelSpawn(int level) {
            std::list<int> levelMonsters = levels[level];
            return std::make_pair(levelMonsters.front(), levelMonsters.back());
        }

        DIFFICULTY getDifficulty() {
            return _difficulty;
        }

    protected:
    private:
        std::map<int, std::tuple<int, int, int>> monsters;
        std::map<int, std::list<int>> levels;
        std::tuple<int, int, int> player;

        DIFFICULTY _difficulty = EASY;
    };
}

#endif /* !GAMEPLAYFACTORY_HPP_ */
