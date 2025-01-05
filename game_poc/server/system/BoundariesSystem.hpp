/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** BoundariesSystem
*/

/**
 * @file BoundariesSystem.hpp
 * @brief Handles entity boundary checks and removal when out of bounds.
 */

#ifndef BOUNDARIESSYSTEM_HPP_
    #define BOUNDARIESSYSTEM_HPP_

    #include "../../../ecs/ECS.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../../../ecs/components/Position.hpp"
    #include "../../../ecs/components/Velocity.hpp"
    #include "../../../ecs/components/Playable.hpp"
    #include "../../shared/components/Health.hpp"
    #include "../components/Hitbox.hpp"

    namespace poc_game
    {
        /**
         * @class BoundariesSystem
         * @brief Manages entity lifecycle based on boundary constraints.
         */
        class BoundariesSystem {
            public:
                /**
                 * @brief Constructor for BoundariesSystem.
                 */
                BoundariesSystem() {}

                /**
                 * @brief Destructor for BoundariesSystem.
                 */
                ~BoundariesSystem() {}

                /**
                 * @brief Checks entities' positions and removes them if they are out of bounds.
                 * @param ecs The ECS manager.
                 * @param windowWidth Width of the game window.
                 * @param windowHeight Height of the game window.
                 * @return A list of entities that have been removed.
                 */
                std::pair<std::list<size_t>, bool> checkAndKillEntities(ecs::ECS &ecs, float windowWidth, float windowHeight)
                    {
                        auto &positions = std::any_cast<ecs::SparseArray<ecs::Position> &>(ecs._components_arrays[typeid(ecs::Position)]);
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(ecs._components_arrays[typeid(ecs::Playable)]);

                        std::pair<std::list<size_t>, bool> dead_entities;

                        bool playerKilled = false;

                        for (size_t i = 0; i < positions.size(); ++i)
                        {
                            if (positions[i].has_value())
                            {
                                auto &position = positions[i].value();

                                if ((position._pos_x > (windowWidth + 100) || position._pos_y > windowHeight ||
                                    position._pos_x < 0 || position._pos_y < 0) && i < playables.size() && playables[i].has_value())
                                {
                                    playerKilled = true;
                                    dead_entities.first.push_front(i);
                                } else if (position._pos_x < 0) {
                                    dead_entities.first.push_front(i);
                                }
                            }
                        }
                        dead_entities.second = playerKilled;
                        return dead_entities;
                    }

            protected:
            private:
        };
    }
#endif /* !BOUNDARIESSYSTEM_HPP_ */
