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

    namespace rtype
    {
        /**
         * @class
         * @brief Music in game.
         */
        class Music {
            public:
                /**
                 * @brief Constructor for the Music class.
                 * @param musicFilePath The path to the music in ogg format
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
                 * @brief Set the music in game.
                 * @param filepath The path to the music to play.
                 */
                void setMusic(const std::string& filePath)
                {
                    if (!music->openFromFile(filePath)) {
                        throw std::runtime_error("Erreur : Impossible de charger le fichier audio : " + filePath);
                    }
                    music->setLoop(true);
                    music->play();
                }

                /**
                 * @brief Play a sound that seems to be a gun shot when the player execute the shoot action in game.
                 * @param filePath the path to the music to play.
                 */
                void setShootMusic(const std::string& filePath)
                {
                    if (!music->openFromFile(filePath)) {
                        throw std::runtime_error("Erreur : Impossible de charger le fichier audio : " + filePath);
                    }
                    if (music->getStatus() == sf::Sound::Playing) {
                        music->stop();
                    }
                    music->setLoop(false);
                    music->play();
                }

            protected:
            private:
                std::shared_ptr<sf::Music> music;
        };
    }

#endif /* !MUSIC_HPP_ */
