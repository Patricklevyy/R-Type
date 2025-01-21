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
        class MusicSystem {
            public:
                MusicSystem() {}
                ~MusicSystem() {}

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
