/*
** EPITECH PROJECT, 2025
** R-TYPE
** File description:
** Room_Create_And_Destroy
*/

#include "Room.hpp"

namespace poc_game
{
    size_t Room::create_player(std::pair<float, float> positions)
    {
        std::cout << "CREATE PLAYER " << _nb_client << std::endl;
        size_t index = getNextIndex();

        _ecs.addComponents<ecs::Direction>(index, ecs::Direction());
        _ecs.addComponents<ecs::Playable>(index, ecs::Playable());
        _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(300));
        _ecs.addComponents<ecs::Position>(
            index, ecs::Position(positions.first, positions.second));
        _ecs.addComponents<Hitbox>(
            index, Hitbox(HitboxFactory::createHitbox(SPRITES::PLAYER)));
        _ecs.addComponents<Allies>(index, Allies());

        return index;
    }

    void Room::spawn_pipes()
    {
        auto current_time = std::chrono::steady_clock::now();
        float elapsed_time =
            std::chrono::duration<float>(current_time - _last_spawn_time)
                .count();
        float SPACE = 320;

        if (elapsed_time >= PIPE_SPAWN_INTERVAL) {
            size_t index = getNextIndex();
            std::pair<int, int> positions =
                PipeFactory::getMonsterSpawnCoordinates(
                    _window_width, _window_height, _random_number);

            _ecs.addComponents<ecs::Position>(index,
                ecs::Position(positions.first, positions.second - SPACE));
            _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(100));
            _ecs.addComponents<ecs::Direction>(index,
                ecs::Direction(
                    ecs::direction::LEFT, ecs::direction::NO_DIRECTION));
            _ecs.addComponents<Hitbox>(
                index, Hitbox(HitboxFactory::createHitbox(SPRITES::PIPE_UP)));
            _ecs.addComponents<Ennemies>(index, Ennemies());

            send_client_new_pipe(index, positions.first,
                positions.second - SPACE, SPRITES::PIPE_DOWN);

            index = getNextIndex();

            _ecs.addComponents<ecs::Position>(index,
                ecs::Position(positions.first, positions.second + SPACE));
            _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(100));
            _ecs.addComponents<ecs::Direction>(index,
                ecs::Direction(
                    ecs::direction::LEFT, ecs::direction::NO_DIRECTION));
            _ecs.addComponents<Hitbox>(
                index, Hitbox(HitboxFactory::createHitbox(SPRITES::PIPE_UP)));
            _ecs.addComponents<Ennemies>(index, Ennemies());

            send_client_new_pipe(index, positions.first,
                positions.second + SPACE, SPRITES::PIPE_UP);

            _last_spawn_time = current_time;
        }
    }
} // namespace poc_game
