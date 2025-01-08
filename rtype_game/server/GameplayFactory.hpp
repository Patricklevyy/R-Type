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
#include "../shared/Enums.hpp"

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

            // Parse player data
            const libconfig::Setting& playerSettings = root["gameplay"]["players"];
            int playerHealth, playerVelocity, playerDamage;
            playerSettings.lookupValue("health", playerHealth);
            playerSettings.lookupValue("velocity", playerVelocity);
            playerSettings.lookupValue("damage", playerDamage);

            player = std::make_tuple(playerHealth, playerVelocity, playerDamage);

            // Parse monsters data
            const libconfig::Setting& monsterSettings = root["gameplay"]["monsters"];
            for (int i = 0; i < monsterSettings.getLength(); ++i) {
                const libconfig::Setting& monster = monsterSettings[i];
                int health, velocity, damage;

                monster.lookupValue("health", health);
                monster.lookupValue("velocity", velocity);
                monster.lookupValue("damage", damage);

                monsters[i + 1] = std::make_tuple(health, velocity, damage); // Monster IDs start at 1
            }

            // Parse boss data
            const libconfig::Setting& bossSettings = root["gameplay"]["boss"];
            for (int i = 0; i < bossSettings.getLength(); ++i) {
                const libconfig::Setting& bossEntry = bossSettings[i];
                int health, velocity, damage;

                bossEntry.lookupValue("health", health);
                bossEntry.lookupValue("velocity", velocity);
                bossEntry.lookupValue("damage", damage);

                boss[i + 1] = std::make_tuple(health, velocity, damage); // Boss IDs start at 1
            }

            // Parse levels data
            const libconfig::Setting& levelsSettings = root["gameplay"]["levels"];
            for (int i = 0; i < levelsSettings.getLength(); ++i) {
                const libconfig::Setting& level = levelsSettings[i];
                std::list<int> ids;

                for (int j = 0; j < level.getLength(); ++j) {
                    int id = level[j]; // Accès par indice pour récupérer les IDs directement
                    ids.push_back(id);
                }
                levels[i + 1] = ids; // Store level data
            }

            // Parse final levels data
            const libconfig::Setting& finalLevelsSettings = root["gameplay"]["final_levels"];
            for (int i = 0; i < finalLevelsSettings.getLength(); ++i) {
                const libconfig::Setting& finalLevel = finalLevelsSettings[i];
                std::list<int> ids;

                for (int j = 0; j < finalLevel.getLength(); ++j) {
                    int id = finalLevel[j]; // Accès par indice pour récupérer les IDs directement
                    ids.push_back(id);
                }
                final_levels[i + 1] = ids; // Store final level data
            }

        }

        // Function to print all the parsed data
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

            std::cout << "Boss Configs:" << std::endl;
            for (const auto& [id, config] : boss) {
                std::cout << "  Boss " << id << ":" << std::endl;
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

            std::cout << "Final Levels Config:" << std::endl;
            for (const auto& [level, ids] : final_levels) {
                std::cout << "  Final Level " << level << ": ";
                for (int id : ids) {
                    std::cout << id << " ";
                }
                std::cout << std::endl;
            }
        }

    protected:
    private:
        std::map<int, std::tuple<int, int, int>> monsters;
        std::map<int, std::tuple<int, int, int>> boss;
        std::map<int, std::list<int>> levels;
        std::map<int, std::list<int>> final_levels;
        std::tuple<int, int, int> player;
    };
}

#endif /* !GAMEPLAYFACTORY_HPP_ */
