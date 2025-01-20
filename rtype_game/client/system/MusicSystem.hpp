/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MusicSystem
*/

/**
 * @file MusicSystem.hpp
 * @brief Header file for the MusicSystem class.
 *
 * This file contains the declaration of the MusicSystem class, which is responsible for 
 * handling music changes within the game.
 */

#ifndef MUSICSYSTEM_HPP_
    #define MUSICSYSTEM_HPP_

    #include "../components/Music.hpp"
    #include "../../../ecs/SparseArray.hpp"

    namespace rtype
    {
        /**
         * @class MusicSystem
         * @brief A class that handles music-related functionalities in the game.
         *
         * The MusicSystem class provides functionality to change the current background music
         * of the game by interacting with the Music component and modifying the corresponding music file path.
         */
        class MusicSystem {
            public:
                /**
                 * @brief Default constructor for the MusicSystem class.
                 */
                MusicSystem() {}
                /**
                 * @brief Destructor for the MusicSystem class.
                 */
                ~MusicSystem() {}

                /**
                 * @brief Changes the current music by setting a new music file path.
                 *
                 * This method retrieves the music component from the ECS system and changes the
                 * music track by setting the new music file path. If the music component is found,
                 * it calls the `setMusic` method to update the music.
                 *
                 * @param components_array The array of components of entities in the ECS system.
                 * @param musicFilePath The file path of the new music to be played.
                 * 
                 * @exception std::exception If there is an issue casting or accessing the music components.
                 */
                void changeMusic(std::unordered_map<std::type_index, std::any> &components_array, std::string musicFilePath)
                {
                    try {
                        auto &musics = std::any_cast<ecs::SparseArray<Music> &>(components_array.at(typeid(Music)));

                        if (musics[0].has_value()) {
                            musics[0].value().setMusic(musicFilePath);
                        }
                    } catch (const std::exception &e) {
                        std::cerr << "[EXCEPTON] " << e.what() << std::endl;
                    } catch (...) {
                        std::cerr << "[UNKNOWN ERROR] Une erreur inconnue s'est produite." << std::endl;
                    }
                }

                void shootMusic(std::unordered_map<std::type_index, std::any> &components_array, std::string musicFilePath)
                {
                    try {
                        auto &musics = std::any_cast<ecs::SparseArray<Music> &>(components_array.at(typeid(Music)));

                        if (musics[0].has_value()) {
                            musics[0].value().setShootMusic(musicFilePath);
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
