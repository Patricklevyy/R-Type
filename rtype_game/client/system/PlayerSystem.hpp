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

            protected:
            private:
        };
    }

#endif /* !PLAYERSYSTEM_HPP_ */
