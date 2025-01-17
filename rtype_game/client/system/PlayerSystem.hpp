/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** PlayerSystem
*/

#ifndef PLAYERSYSTEM_HPP_
    #define PLAYERSYSTEM_HPP_

    #include "../../../ecs/components/Playable.hpp"
    #include "../../../ecs/SparseArray.hpp"
    #include "../components/Displayable.hpp"
    #include "../components/Life.hpp"
    #include "../../shared/components/Health.hpp"


    namespace rtype
    {
        class PlayerSystem {
            public:
                PlayerSystem() {}
                ~PlayerSystem() {}

                /**
                 * @brief Return the index of the player, used only by the client.
                 */
                int getIndexPlayer(std::unordered_map<std::type_index, std::any> &components_array)
                {
                    try {
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);

                        for (std::size_t i = 0; i < playables.size(); ++i)
                        {
                            if (i < playables.size() && playables[i].has_value())
                                return i;
                        }
                        return -1;
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTIN] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                    return -1;
                }

                void changePlayerSprite(std::unordered_map<std::type_index, std::any> &components_array, size_t index, SPRITES sprite)
                {
                    try {
                        auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                        auto &displayables = std::any_cast<ecs::SparseArray<Displayable> &>(components_array[typeid(Displayable)]);

                        if (index < playables.size() && playables[index].has_value() && index < displayables.size() && displayables[index].has_value()) {
                            displayables[index].value().setSprite(sprite);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTIN] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

                std::pair<bool, int> updatePlayerLife(std::unordered_map<std::type_index, std::any> &components_array, size_t index, int health) {
                    auto &playables = std::any_cast<ecs::SparseArray<ecs::Playable> &>(components_array[typeid(ecs::Playable)]);
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);

                    if (index < playables.size() && playables[index].has_value() && index < healths.size() && healths[index].has_value()) {
                        healths[index].value()._health = health;
                        if (healths[index].value()._health > healths[index].value()._max_heath) {
                            healths[index].value()._health = healths[index].value()._max_heath;
                        }
                        return std::make_pair(true, healths[index].value()._health);
                    }
                    return std::make_pair(false, 0);
                }

                void updateLifeDisplay(std::unordered_map<std::type_index, std::any> &components_array, size_t index) {
                    auto &life = std::any_cast<ecs::SparseArray<Life> &>(components_array[typeid(Life)]);
                    auto &healths = std::any_cast<ecs::SparseArray<Health> &>(components_array[typeid(Health)]);
                    auto &displayable = std::any_cast<ecs::SparseArray<Displayable> &>(components_array[typeid(Displayable)]);

                    for (std::size_t i = 0; i < life.size(); ++i)
                    {
                        if (life[i].has_value() && i < displayable.size() && displayable[i].has_value() && index < healths.size() && healths[index].has_value()) {
                            std::tuple<float, float, float> scale = SpriteFactory::getSpriteScaleAndSpeed(SPRITES::LIFE_RED);

                            float new_size = (std::get<0>(scale) / healths[index].value()._max_heath) * healths[index].value()._health;

                            displayable[i].value().setSpriteScale(new_size, std::get<1>(scale));
                        }
                    }
                }

            protected:
            private:
        };
    }

#endif /* !PLAYERSYSTEM_HPP_ */
