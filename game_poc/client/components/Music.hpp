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
         * @brief Represents a music object for playing audio.
         */
        class Music {
            public:

                /**
                 * @brief Constructs a music object with a given file path.
                 */
                Music(const std::string& musicFilePath) : music(std::make_shared<sf::Music>())
                {
                    if (!music->openFromFile(musicFilePath)) {
                        throw std::runtime_error("Erreur : Impossible de charger le fichier audio : " + musicFilePath);
                    }
                    music->setLoop(true);
                    music->play();
                }

                ~Music()
                {
                    if (music.use_count() == 1) {
                        music->stop();
                    }
                }

                /**
                 * @brief Plays the music.
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
