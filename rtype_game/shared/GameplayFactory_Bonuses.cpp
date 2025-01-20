/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** GameplayFactory_Bonuses
*/

#include "GameplayFactory.hpp"

namespace rtype
{
    int GameplayFactory::getBonusSpeed() const
    {
        return bonus_speed;
    }

    int GameplayFactory::getShieldDuration()
    {
        return bonuses[BONUS::SHIELD].second;
    }

    int GameplayFactory::getLifeBonus()
    {
        return bonuses[BONUS::LIFE].first;
    }

    int GameplayFactory::getVelocityDurationBonus()
    {
        return bonuses[BONUS::VELOCITY].second;
    }

    int GameplayFactory::getVelocityBoostBonus()
    {
        return bonuses[BONUS::VELOCITY].first;
    }

    int GameplayFactory::getWeaponDurationBonus()
    {
        return bonuses[BONUS::WEAPON].second;
    }

    int GameplayFactory::getWeaponBoostBonus()
    {
        return bonuses[BONUS::WEAPON].first;
    }

    BONUS GameplayFactory::getRandomBonuses(int rand)
    {
        if (rand <= 0 || rand >= BONUS::MAX_BONUS)
            throw std::invalid_argument("Id for bonus not found.");
        return static_cast<BONUS>(rand);
    }

    SPRITES GameplayFactory::getSpriteBonus(BONUS bonus)
    {
        switch (bonus) {
            case VELOCITY: return SPRITES::SPEED_DROP;
            case LIFE: return SPRITES::LIFE_DROP;
            case WEAPON: return SPRITES::WEAPON_DROP;
            case SHIELD: return SPRITES::SHIELD_DROP;
            default:
                throw std::invalid_argument("No Id found for bonus sprite");
        }
    }
} // namespace rtype