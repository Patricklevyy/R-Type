/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Init
*/

#include "Client.hpp"

namespace poc_game
{
    void Client::init_ecs_client_registry()
    {
        _ecs.addRegistry<Window>();
        _ecs.addRegistry<Displayable>();
        _ecs.addRegistry<Health>();
        _ecs.addRegistry<Shader>();
        _ecs.addRegistry<Levels>();
        _ecs.addRegistry<TempDisplay>();
        _ecs.addRegistry<Music>();
    }

    void Client::init_game(ecs::udp::Message &message)
    {
        std::cout << "INIT\n\n\n\n\n\n\n\n\n\n\n\n\n" << std::endl;
        size_t pos = message.params.find(':');

        std::string player_room = message.params.substr(0, pos);
        std::string entities = message.params.substr(pos + 1);

        std::cout << "PLAYER : " << player_room << "ENTITIES : " << entities
                  << std::endl;
        std::tuple<float, float, int> pos_port =
            Utils::parsePositionAndRoomPort(player_room);

        std::list<size_t> deads = _ath_system.removePlayButtons(_ecs);
        for (const auto &entity_id : deads) {
            _kill_system.killEntity(_ecs, entity_id);
        }
        setRoomAdress(std::get<2>(pos_port));
        init_player(message.id, std::get<0>(pos_port), std::get<1>(pos_port));
        _in_menu = false;
    }

    void Client::init_window_and_background()
    {
        size_t index = getNextIndex();

        Window window(_window_width, _window_height, "R-Type");
        _ecs.addComponents<Window>(index, window);
        _ecs.addComponents<Music>(
            index, Music("game_poc/assets/music/onSIGHT.ogg"));
        _ecs.addComponents<Displayable>(
            index, Displayable(SPRITES::BACKGROUND));
        _ecs.addComponents<ecs::Position>(index, ecs::Position(0, 0));
        _ecs.addComponents<ecs::Velocity>(index, ecs::Velocity(10));
        _ecs.addComponents<Shader>(index, Shader(FILTER_MODE::Neutral));
    }

    void Client::init_player(unsigned int server_id, float x, float y)
    {
        size_t index = getNextIndex();

        _ecs.addComponents<Displayable>(index, Displayable(SPRITES::PLAYER));
        _ecs.addComponents<ecs::Position>(index, ecs::Position(x, y));
        _ecs.addComponents<ecs::Playable>(index, ecs::Playable());

        ecs_server_to_client[server_id] = index;
        ecs_client_to_server[index] = server_id;
    }

    void Client::init_play_button()
    {
        size_t index = getNextIndex();

        _ecs.addComponents<Displayable>(
            index, Displayable(SPRITES::PLAY_BUTTON));
        _ecs.addComponents<ecs::Position>(
            index, ecs::Position(_window_width / 2, _window_height / 2));
        _ecs.addComponents<TempDisplay>(index, TempDisplay());
    }

    void Client::init_window_size(const std::string &file_path)
    {
        libconfig::Config cfg;

        try {
            cfg.readFile(file_path.c_str());

            const libconfig::Setting &root = cfg.getRoot();
            const libconfig::Setting &client = root["client"];

            if (!client.lookupValue("window_width", _window_width)) {
                std::cerr << "Erreur : 'window_x' introuvable dans le fichier "
                             "de configuration."
                          << std::endl;
            }

            if (!client.lookupValue("window_height", _window_height)) {
                std::cerr << "Erreur : 'window_y' introuvable dans le fichier "
                             "de configuration."
                          << std::endl;
            }
        } catch (const libconfig::FileIOException &fioex) {
            std::cerr
                << "Erreur : Impossible de lire le fichier de configuration."
                << std::endl;
        } catch (const libconfig::ParseException &pex) {
            std::cerr << "Erreur de parsing au niveau " << pex.getFile() << ":"
                      << pex.getLine() << " - " << pex.getError() << std::endl;
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Erreur : Paramètre introuvable dans le fichier de "
                         "configuration."
                      << std::endl;
        }
    }

    void Client::init_all()
    {
        if (!_udpClient->initialize("game_poc/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeClientExceptions(
                "Failed to initialize client");
        }
        init_window_size("game_poc/config/client_config.conf");
        _timer->init("game_poc/config/client_config.conf", false);
        _udpClient->startReceiving();
        _ecs.init_basic_registry();
        init_ecs_client_registry();
        init_window_and_background();
        init_play_button();
        init_subscribe_event_bus();
        _eventBus.emit(POC_GAME_ACTIONS::START_LISTEN_EVENT);
    }
} // namespace poc_game