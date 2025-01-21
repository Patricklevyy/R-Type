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
        /**
         * @class ScoreSystem
         * @brief Handle the score of the player.
         */
        class ScoreSystem {
            public:
                /**
                 * @brief Default constructor for the ScoreSystem class.
                 */
                ScoreSystem() {}

                /**
                 * @brief Default destructor for the ScoreSystem class.
                 */
                ~ScoreSystem() {}

                /**
                 * @brief Updates the score display when a monster is killed.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @param score The new score value as a string.
                 */
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
