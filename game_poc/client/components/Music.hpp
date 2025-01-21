/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Music
*/

#ifndef MUSIC_HPP_
    #define MUSIC_HPP_

    #include <SFML/Audio.hpp>
    #include <memory>
    #include <string>
    #include <iostream>
    #include <stdexcept>

    namespace poc_game
    {
        /**
         * @class Music
         * @brief Class that handles in game Music.
         */
        class Music {
            public:
                /**
                 * @brief Constructor for the Music class.
                 * @param musicFilePath The path to the music file to be played.
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
                 * @brief Destructor for the Music class.
                 */
                ~Music()
                {
                    if (music.use_count() == 1) {
                        music->stop();
                    }
                }


                /**
                 * @brief Change the current music track.
                 * @param filePath The path to the new music track to be played.
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
