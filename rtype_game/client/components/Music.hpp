/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Music
*/

/**
 * @file Music.hpp
 * @brief Header file for the Music class.
 *
 * This file contains the declaration of the Music class, which is responsible for handling
 * background music in the R-Type game client.
 */

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_

    #include <SFML/Audio.hpp>
    #include <memory>
    #include <string>
    #include <iostream>
    #include <stdexcept>

    namespace rtype
    {
        /**
         * @class Music
         * @brief Manages a SFML music object for playing background music.
         */
        class Music {
            public:
                /**
                 * @brief Constructs a Music object with a music file.
                 * 
                 * @param musicFilePath The file path to the music file.
                 * @throws std::runtime_error If the music file cannot be loaded.
                 * @note The music file will be played in a loop.
                 */
                Music(const std::string& musicFilePath) : music(std::make_shared<sf::Music>())
                {
                    if (!music->openFromFile(musicFilePath)) {
                        throw std::runtime_error("Erreur : Impossible de charger le fichier audio : " + musicFilePath);
                    }
                    music->setLoop(true);
                    music->play();
                }

                /**
                 * @brief Destructor for Music.
                 * 
                 * Stops the current music and cleans up any resources used by the Music instance.
                 */
                ~Music()
                {
                    if (music.use_count() == 1) {
                        music->stop();
                    }
                }

                /**
                 * @brief Sets a new music file to be played.
                 * 
                 * @param filePath The file path to the new music file.
                 * @throws std::runtime_error If the music file cannot be loaded.
                 */
                void setMusic(const std::string& filePath)
                {
                    if (!music->openFromFile(filePath)) {
                        throw std::runtime_error("Erreur : Impossible de charger le fichier audio : " + filePath);
                    }
                    music->setLoop(true);
                    music->play();
                }

            protected:
            private:
                std::shared_ptr<sf::Music> music;
        };
    }

#endif /* !MUSIC_HPP_ */
