/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Enums
*/

/**
 * @file Enums.hpp
 * @brief Defines various enumerations for actions, sprites, and visual filters in the R-Type game.
 */

#ifndef ENUMS_HPP_
    #define ENUMS_HPP_

    namespace rtype
    {

        /**
         * @enum RTYPE_ACTIONS
         * @brief Defines all the possible actions in the R-Type game.
         */
        enum RTYPE_ACTIONS
        {
            UNDEFINED = -1,
            CREATE_ROOM,
            JOIN_ROOM,
            LEAVE_ROOM,
            MOVE_UP,
            MOVE_UP_STOP,
            MOVE_RIGHT,
            MOVE_RIGHT_STOP,
            MOVE_DOWN,
            MOVE_DOWN_STOP,
            MOVE_LEFT,
            MOVE_LEFT_STOP,
            CHECK_EVENT_WINDOW,
            CREATE_CLIENT,
            CREATE_TEAMMATE,
            UPDATE_POSITIONS,
            UPDATE_DIRECTION,
            UPDATE_PLAYER_DIRECTION,
            UPDATE_PLAYER_POSITION,
            START_LISTEN_EVENT,
            STOP_LISTEN_EVENT,
            GET_WINDOW_EVENT,
            PLAYER_SHOOT,
            ENEMY_SHOOT,
            CREATE_PROJECTILE,
            CREATE_MONSTER,
            MOVE_MONSTERS,
            KILL_PROJECTILES,
            CHECK_OFF_SCREEN,
            UPDATE_GAME_STATUS,
            CHECK_COLLISIONS,
            KILL_ENTITY,
            CHECK_LIFES,
            GET_ALL_ROOMS,
            CHECK_LEVEL_FINISHED,
            RENDER_WINDOW,
            START_LEVEL,
            MOVE_BACKGROUND,
            EXECUTE_LEVEL,
            CREATE_PLAYER,
            FAIL_LEVEL,
            WIN_LEVEL,
            UPDATE_POSITIONS_FROM_SERVER,
            UPDATE_PARTIALS_POSITIONS_FROM_SERVER,
            REMOVE_ATH,
            UPDATE_SCORE,
            SPAWN_ASTEROIDE,
            CHECK_BONUS_COLLISIONS,
            CHECK_BONUS,
            PUT_SHIELD,
            REMOVE_SHIELD,
            UP_VELOCITY,
            DOWN_VELOCITY,
            UPDATE_LIFE,
            PUT_WEAPON,
            REMOVE_WEAPON,
            CLIENT_LEAVE,
            MAX_ACTION
        };

        /**
         * @enum SPRITES
         * @brief Defines sprite identifiers for game assets.
         */
        enum SPRITES
        {
            SIMPLE_MONSTER = 1,
            ADVANCED_MONSTER = 2,
            SUPER_MONSTER = 3,
            MEGA_MONSTER = 4,
            SIMPLE_BOSS = 5,
            MENU_BACKGROUND,
            GAME_BACKGROUND,
            MY_PLAYER_SHIP,
            PLAYER_SIMPLE_MISSILE,
            PLAYER_CHARGED_SHOOT,
            CHARGED_ANIMATION,
            MONSTER_SIMPLE_MISSILE,
            MONSTER_MULTIPLE_MISSILE,
            BABY_PROJECTILE,
            FIRE_BALL,
            BOSS_PROJECTILE,
            OTHER_PLAYER_SHIP,
            OTHER_PLAYER_SHIP_SHIELD,
            LOOSER_SCREEN,
            WIN_SCREEN,
            LEVEL1,
            LEVEL2,
            LEVEL_BOSS,
            LEVEL_LOCK,
            WEAPON_DROP,
            LIFE_DROP,
            VELOCITY_DROP,
            SHIELD_DROP,
            SPEED_DROP,
            ASTEROIDE,
            MY_PLAYER_SHIP_SHIELD,
            LIFE_RECTANGLE,
            LIFE_RED,
            LIFE_HEART,
            MY_PLAYER_SHIP_WEAPON,
            OTHER_PLAYER_SHIP_WEAPON,
            PLAYER_RED_MISSILE,
            PLAYER_RED_CHARGED_SHOOT,
            MAX_SPRITE
        };

        /**
         * @enum MONSTERS
         * @brief Enum Monsters.
         */
        enum MONSTER
        {
            MONSTER1 = 1,
            MONSTER2,
            MAX_MONSTER
        };

        /**
         * @enum BOSSES
         * @brief Enum Bosss.
         */
        enum BOSSES
        {
            BOSS1 = 1,
            MAX_BOSS
        };

        /**
         * @enum LEVELS
         * @brief Defines stages of the game.
         */
        enum LEVELS
        {
            UN = 1,
            DEUX,
            BOSS
        };

        /**
         * @enum DIFFICULTY
         * @brief Defines difficulty of the monsters for customization.
         */
        enum DIFFICULTY
        {
            EASY,
            MEDIUM,
            HARD,
            IMPOSSIBLE
        };

        /**
         * @enum FILTER_MODE
         * @brief Defines visual filter modes for accessibility and customization.
         */
        enum FILTER_MODE {
            Neutral,
            Protanopia,
            Deuteranopia,
            Tritanopia,
            Inverted
        };

        /**
         * @enum BONUS
         * @brief Spawn a weapon when a monster is killed
         */
        enum BONUS {
            VELOCITY = 1,
            LIFE,
            SHIELD,
            WEAPON,
            MAX_BONUS
        };
    }

#endif /* !ENUMS_HPP_ */
