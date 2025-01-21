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

    namespace rtype
    {
      /**
       * @class MusicSystem
       * @brief Handles animations and interactions in the game, including level management and mouse input detection.
       */
        class MusicSystem {
            public:
                /**
                 * @brief Default constructor for the MusicSystem class.
                 */
                MusicSystem() {}

                /**
                 * @brief Default destructor for the MusicSystem class.
                 */
                ~MusicSystem() {}

                /**
                 * @brief Changes the background music of the game.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @param musicFilePath The file path to the new music file to be played.
                 */
                void changeMusic(std::unordered_map<std::type_index, std::any> &components_array, std::string musicFilePath)
                {
                    try {
                        auto &musics = std::any_cast<ecs::SparseArray<Music> &>(components_array.at(typeid(Music)));

                        if (musics[0].has_value()) {
                            musics[0].value().setMusic(musicFilePath, true);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTON] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

                /**
                 * @brief Changes the shooting sound effect of the game.
                 * @param components_array A reference to a map containing ECS components indexed by their type.
                 * @param musicFilePath The file path to the new shooting sound file to be played.
                 */
                void shootMusic(std::unordered_map<std::type_index, std::any> &components_array, std::string musicFilePath)
                {
                    try {
                        auto &musics = std::any_cast<ecs::SparseArray<Music> &>(components_array.at(typeid(Music)));

                        if (musics[0].has_value()) {
                            musics[0].value().setMusic(musicFilePath, false);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTON] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

            protected:
            private:
        };
    }


#endif /* !MUSICSYSTEM_HPP_ */
