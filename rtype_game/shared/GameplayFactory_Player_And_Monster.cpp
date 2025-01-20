/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameplayFactory_Player_And_Monster
*/

#include "GameplayFactory.hpp"

namespace rtype
{
    int GameplayFactory::getPlayerVelocity() {
            return std::get<1>(player);
        }

        int GameplayFactory::getPlayerHealth() {
            return std::get<0>(player);
        }

        int GameplayFactory::getPlayerPlayerDamage() {
            return std::get<2>(player);
        }

        int GameplayFactory::getMonsterVelocity(SPRITES id) {
            return std::get<1>(monsters[id]);
        }

        int GameplayFactory::getMonsterHealth(SPRITES id) {
            return std::get<0>(monsters[id]);
        }

        int GameplayFactory::getMonsterDamage(SPRITES id) {
            return std::get<2>(monsters[id]);
        }

        int GameplayFactory::getBossVelocity(SPRITES id) {
            return std::get<1>(bosses[id]);
        }

        int GameplayFactory::getBossHealth(SPRITES id) {
            return std::get<0>(bosses[id]);
        }

        int GameplayFactory::getBossDamage(SPRITES id) {
            return std::get<2>(bosses[id]);
        }

        int GameplayFactory::getMonsterBodyDamage(SPRITES sprite) {
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

        int GameplayFactory::getProjectilesDamage(SPRITES sprite) {
            switch (sprite)
            {
            case PLAYER_SIMPLE_MISSILE:
                return getPlayerPlayerDamage();
            case PLAYER_CHARGED_SHOOT:
                return (getPlayerPlayerDamage() * 3);
            case PLAYER_RED_MISSILE:
                return (getPlayerPlayerDamage() * 3);
            case PLAYER_RED_CHARGED_SHOOT:
                return (getPlayerPlayerDamage() * 5);
            case MONSTER_SIMPLE_MISSILE:
                return getMonsterDamage(SPRITES::SIMPLE_MONSTER);
            case MONSTER_MULTIPLE_MISSILE:
                return getMonsterDamage(SPRITES::ADVANCED_MONSTER);
            case BABY_PROJECTILE:
                return getMonsterDamage(SPRITES::SUPER_MONSTER);
            case FIRE_BALL:
                return getMonsterDamage(SPRITES::MEGA_MONSTER);
            case BOSS_PROJECTILE:
                return getMonsterDamage(SPRITES::SIMPLE_BOSS);
            case ASTEROIDE:
                return 20;
            default:
                std::cerr << "Monster Id not found" << std::endl;
                return 0;
            }
        }

        int GameplayFactory::getMonsterScoreValue(SPRITES sprite) {
            switch (sprite)
            {
            case SPRITES::SIMPLE_BOSS:
                return 100;
            default:
                return 1;
            }
        }

        int GameplayFactory::getPlayerBodyDamage() {
            return 20;
        }

        std::pair<int, int> GameplayFactory::getMonsterLevelSpawn(int level) {
            std::list<int> levelMonsters = levels[level];
            return std::make_pair(levelMonsters.front(), levelMonsters.back());
        }

        std::pair<int, int> GameplayFactory::getBossLevelSpawn() {
            return std::make_pair(SIMPLE_BOSS, SIMPLE_BOSS);
        }
}