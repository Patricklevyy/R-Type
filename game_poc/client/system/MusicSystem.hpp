/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicSystem
*/

#ifndef MUSICSYSTEM_HPP_
    #define MUSICSYSTEM_HPP_

    #include "../components/Music.hpp"
    #include "../../../ecs/SparseArray.hpp"

    namespace poc_game
    {
        /**
         * @class MusicSystem
         * @brief Class responsible for handling in game music.

         */
        class MusicSystem {
            public:
                /**
                 * @brief Default constructor for MusicSystem class.
                 */
                MusicSystem() {}

                /**
                 * @brief Default destructor for MusicSystem class.
                 */
                ~MusicSystem() {}

                /**
                 * @brief Change the music in the game.
                 * @param components_array The array of ECS components containing the music component.
                 * @param musicFilePath The file path of the new music to be played.
                 */
                void changeMusic(std::unordered_map<std::type_index, std::any> &components_array, std::string musicFilePath)
                {
                    try {
                        auto &musics = std::any_cast<ecs::SparseArray<Music> &>(components_array.at(typeid(Music)));

                        if (musics[0].has_value()) {
                            musics[0].value().setMusic(musicFilePath);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTION] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

            protected:
            private:
        };
    }


#endif /* !MUSICSYSTEM_HPP_ */
