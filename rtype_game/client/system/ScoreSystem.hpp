/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ScoreSystem
*/

/**
 * @file ScoreSystem.hpp
 * @brief Header file for the ScoreSystem class.
 *
 * This file contains the declaration of the ScoreSystem class, responsible for updating
 * and displaying the player's score on the screen.
 */

#ifndef SCORESYSTEM_HPP_
    #define SCORESYSTEM_HPP_

    #include "../components/Text.hpp"
    #include "../../../ecs/SparseArray.hpp"

    namespace rtype
    {
        /**
         * @class ScoreSystem
         * @brief A system that updates and manages the player's score display.
         *
         * The ScoreSystem class is responsible for updating the in-game score displayed
         * on the user interface. It works by modifying the corresponding Text components
         * in the ECS (Entity-Component-System) framework to reflect the current score.
         */
        class ScoreSystem {
            public:
                /**
                 * @brief Default constructor for the ScoreSystem class.
                 */
                ScoreSystem() {}
                /**
                 * @brief Destructor for the ScoreSystem class.
                 */
                ~ScoreSystem() {}

                /**
                 * @brief Update the displayed score in the game.
                 *
                 * This method updates all Text components that represent the score display
                 * by setting them to show the given score.
                 *
                 * @param components_array The array of components of entities in the ECS system.
                 * @param score The new score string to display.
                 * 
                 * @exception std::exception If there is an error accessing the text components.
                 * @exception Unknown exception If an unknown error occurs.
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
