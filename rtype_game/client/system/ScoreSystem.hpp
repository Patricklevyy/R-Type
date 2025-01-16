/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScoreSystem
*/

#ifndef SCORESYSTEM_HPP_
    #define SCORESYSTEM_HPP_

    #include "../components/Text.hpp"
    #include "../../../ecs/SparseArray.hpp"

    namespace rtype
    {
        class ScoreSystem {
            public:
                ScoreSystem() {}
                ~ScoreSystem() {}

                void updateScore(std::unordered_map<std::type_index, std::any> &components_array, std::string score)
                {
                    auto &texts = std::any_cast<ecs::SparseArray<Text> &>(components_array[typeid(Text)]);

                    for (std::size_t i = 0; i < texts.size(); ++i)
                        {
                            if (i < texts.size() && texts[i].has_value()) {
                                texts[i].value().setText("SCORE : " + score);
                            }
                        }

                }

            protected:
            private:
        };
    }

#endif /* !SCORESYSTEM_HPP_ */
