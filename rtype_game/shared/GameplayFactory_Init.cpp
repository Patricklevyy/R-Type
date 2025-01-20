/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameplayFactory_Init
*/

#include "GameplayFactory.hpp"

namespace rtype
{
    void GameplayFactory::init(const std::string& filename) {
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

            const libconfig::Setting& bonusSpeedSettings = root["gameplay"]["bonus"];
            int bonus_spe;
            bonusSpeedSettings.lookupValue("speed", bonus_spe);
            bonus_speed = bonus_spe;

            const libconfig::Setting& bonusVelocitySettings = root["gameplay"]["bonus"]["velocity"];
            int boost, duration;
            bonusVelocitySettings.lookupValue("boost", boost);
            bonusVelocitySettings.lookupValue("duration", duration);

            bonuses[BONUS::VELOCITY] = std::make_pair(boost, duration);

            const libconfig::Setting& bonusLifeSettings = root["gameplay"]["bonus"]["life"];
            bonusLifeSettings.lookupValue("boost", boost);
            bonuses[BONUS::LIFE] = std::make_pair(boost, duration);

            const libconfig::Setting& bonusShieldSettings = root["gameplay"]["bonus"]["shield"];
            bonusShieldSettings.lookupValue("duration", duration);
            bonuses[BONUS::SHIELD] = std::make_pair(boost, duration);

            const libconfig::Setting& bonusWeaponSettings = root["gameplay"]["bonus"]["weapon"];
            bonusWeaponSettings.lookupValue("duration", duration);
            bonuses[BONUS::WEAPON] = std::make_pair(boost, duration);
        }
}