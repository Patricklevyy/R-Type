/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Timer
*/

#include "Timer.hpp"

namespace rtype
{
    Timer::Timer() {}

    Timer::~Timer() {}

    float Timer::getTps() const
    {
        return _tps;
    }

    void Timer::init(const std::string &configFile, bool isServer)
    {
        libconfig::Config cfg;

        try
        {
            cfg.readFile(configFile.c_str());

            if (isServer)
            {
                if (cfg.exists("server.tps"))
                {
                    int tps = cfg.lookup("server.tps");
                    if (tps > 0)
                    {
                        _tps = tps;
                        tps_duration = std::chrono::duration<float>(1.0f / tps);
                        std::cout << "Serveur: TPS configuré à " << tps << " (" << (1.0f / tps) << " secondes par tick)" << std::endl;
                    }
                    else
                    {
                        throw rtype::ERROR::InvalidTpsOrFpsExceptions("Server TPS doit être supérieur à 0");
                    }
                }
                else
                {
                    std::cerr << "Le paramètre 'server.tps' est manquant dans la configuration." << std::endl;
                }
            }
            else
            {
                if (cfg.exists("client.tps"))
                {
                    int tps = cfg.lookup("client.tps");
                    if (tps > 0)
                    {
                        _tps = tps;
                        tps_duration = std::chrono::duration<float>(1.0f / tps);
                        std::cout << "Client: TPS configuré à " << tps << " (" << (1.0f / tps) << " secondes par tick)" << std::endl;
                    }
                    else
                    {
                        throw rtype::ERROR::InvalidTpsOrFpsExceptions("Client tps doit être supérieur à 0");
                    }
                }
                else
                {
                    std::cerr << "Le paramètre 'client.tps' est manquant dans la configuration." << std::endl;
                }
                if (cfg.exists("client.fps"))
                {
                    int fps = cfg.lookup("client.fps");
                    if (fps > 0)
                    {
                        fps_duration = std::chrono::duration<float>(1.0f / fps);
                        std::cout << "Client: FPS configuré à " << fps << " (" << (1.0f / fps) << " secondes par image)" << std::endl;
                    }
                    else
                    {
                        throw rtype::ERROR::InvalidTpsOrFpsExceptions("Client fps doit être supérieur à 0");
                    }
                }
                else
                {
                    std::cerr << "Le paramètre 'client.fps' est manquant dans la configuration." << std::endl;
                }
            }
        }
        catch (const libconfig::FileIOException &)
        {
            std::cerr << "Erreur : Impossible d'ouvrir le fichier de configuration." << std::endl;
        }
        catch (const libconfig::ParseException &e)
        {
            std::cerr << "Erreur de syntaxe dans le fichier de configuration (" << e.getFile() << ":" << e.getLine() << ") : " << e.getError() << std::endl;
        }
        catch (std::exception &e)
        {
            std::cerr << std::endl
                      << e.what() << std::endl;
        }
    }

    void Timer::waitTPS()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = now - last_tps_tick;

        if (elapsed < tps_duration)
        {
            std::this_thread::sleep_for(tps_duration - elapsed);
        }

        last_tps_tick = std::chrono::high_resolution_clock::now();
    }

    void Timer::waitFPS()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = now - last_fps_tick;

        if (elapsed < fps_duration)
        {
            std::this_thread::sleep_for(fps_duration - elapsed);
        }

        last_fps_tick = std::chrono::high_resolution_clock::now();
    }
}
