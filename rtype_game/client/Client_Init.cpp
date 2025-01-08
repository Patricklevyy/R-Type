/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_Init
*/

#include "Client.hpp"

namespace rtype
{
     void Client::init_ecs_client_registry()
    {
        _ecs.addRegistry<Window>();
        _ecs.addRegistry<Displayable>();
        _ecs.addRegistry<Shader>();
        _ecs.addRegistry<Levels>();
        _ecs.addRegistry<LevelStatus>();
        _ecs.addRegistry<Music>();
        _ecs.addRegistry<Text>();
    }

    void Client::init_window_and_background()
    {
        Window window(_window_width, _window_height, "R-Type");
        _ecs.addComponents<Window>(_index_ecs_client, window);
        _ecs.addComponents<Music>(_index_ecs_client, Music("assets/musics/gad.ogg"));
        _ecs.addComponents<Displayable>(_index_ecs_client, Displayable(SPRITES::MENU_BACKGROUND));
        _ecs.addComponents<ecs::Position>(_index_ecs_client, ecs::Position(0, 0));
        _ecs.addComponents<ecs::Velocity>(_index_ecs_client, ecs::Velocity(10));
        _ecs.addComponents<Shader>(_index_ecs_client, Shader(FILTER_MODE::Neutral));
        _index_ecs_client++;
    }

    void Client::reset_level_lock()
    {
        _levels_wins[LEVELS::UN] = true;
        _levels_wins[LEVELS::DEUX] = false;
        _levels_wins[LEVELS::BOSS] = false;
    }

    void Client::init_window_size(const std::string &file_path)
    {
        libconfig::Config cfg;

        try {
            cfg.readFile(file_path.c_str());

            const libconfig::Setting &root = cfg.getRoot();
            const libconfig::Setting &client = root["client"];

            if (!client.lookupValue("window_width", _window_width)) {
                std::cerr << "Erreur : 'window_x' introuvable dans le fichier de configuration." << std::endl;
            }

            if (!client.lookupValue("window_height", _window_height)) {
                std::cerr << "Erreur : 'window_y' introuvable dans le fichier de configuration." << std::endl;
            }
        } catch (const libconfig::FileIOException &fioex) {
            std::cerr << "Erreur : Impossible de lire le fichier de configuration." << std::endl;
        } catch (const libconfig::ParseException &pex) {
            std::cerr << "Erreur de parsing au niveau " << pex.getFile()
                      << ":" << pex.getLine() << " - " << pex.getError() << std::endl;
        } catch (const libconfig::SettingNotFoundException &nfex) {
            std::cerr << "Erreur : Paramètre introuvable dans le fichier de configuration." << std::endl;
        }
    }

    void Client::init_all()
    {
        if (!_udpClient->initialize("rtype_game/config/udp_config.conf")) {
            throw ERROR::FailedToInitializeClientExceptions("Failed to initialize client");
        }
        _gameplay_factory = std::make_shared<GameplayFactory>();
        _gameplay_factory->init("rtype_game/config/gameplay_config.conf");
        init_window_size("rtype_game/config/client_config.conf");
        _timer->init("rtype_game/config/client_config.conf", false);
        _udpClient->startReceiving();
        _ecs.init_basic_registry();
        init_ecs_client_registry();
        init_window_and_background();
        init_subscribe_event_bus();
        _eventBus.emit(RTYPE_ACTIONS::START_LISTEN_EVENT);
    }

    void Client::put_level_lock(LEVELS level, int x, int y)
    {
        if (!_levels_wins[level]) {
            size_t index = getNextIndex();
            _ecs.addComponents<ecs::Position>(index, ecs::Position(x + 55, y + 50));
            _ecs.addComponents<Displayable>(index, Displayable(SPRITES::LEVEL_LOCK));
            _ecs.addComponents<Levels>(index, Levels(LEVELS::UN));
        }
    }

    void Client::init_levels_sprites()
    {
        size_t index = getNextIndex();

        int x, y;

        x = (_window_width / 4) - (SpriteFactory::getMaxTextureSizeForSprite(SPRITES::LEVEL1).first / 2);
        y = _window_height - 400;

        _ecs.addComponents<ecs::Position>(index, ecs::Position(x, y));
        _ecs.addComponents<Displayable>(index, Displayable(SPRITES::LEVEL1));
        _ecs.addComponents<Levels>(index, Levels(LEVELS::UN));

        index = getNextIndex();
        x = (_window_width / 2) - (SpriteFactory::getMaxTextureSizeForSprite(SPRITES::LEVEL2).first / 2);

        _ecs.addComponents<ecs::Position>(index, ecs::Position(x, y));
        _ecs.addComponents<Displayable>(index, Displayable(SPRITES::LEVEL2));
        _ecs.addComponents<Levels>(index, Levels(LEVELS::DEUX));

        put_level_lock(LEVELS::DEUX, x, y);

        index = getNextIndex();
        x = ((_window_width / 4) * 3) - (SpriteFactory::getMaxTextureSizeForSprite(SPRITES::LEVEL_BOSS).first / 2);

        _ecs.addComponents<ecs::Position>(index, ecs::Position(x, y));
        _ecs.addComponents<Displayable>(index, Displayable(SPRITES::LEVEL_BOSS));
        _ecs.addComponents<Levels>(index, Levels(LEVELS::BOSS));
        put_level_lock(LEVELS::BOSS, x, y);
    }

    void Client::init_score()
    {
        size_t index = getNextIndex();

        _ecs.addComponents<Text>(index, Text("SCORE : 0", "assets/fonts/komikax.ttf"));
    }

    void Client::init_game(ecs::udp::Message &message)
    {
        size_t pos = message.params.find(':');

        std::string player_room = message.params.substr(0, pos);
        std::string entities = message.params.substr(pos + 1);

        std::cout << "PLAYER : " << player_room << "ENTITIES : " << entities << std::endl;
        std::tuple<float, float, int> pos_port = Command_checker::parsePositionAndRoomPort(player_room);

        _render_window_system.changeBackground(_ecs._components_arrays, SPRITES::GAME_BACKGROUND);
        _music_system.changeMusic(_ecs._components_arrays, "assets/musics/macron.ogg");
        setRoomAdress(std::get<2>(pos_port));
        createPlayer(message.id, std::get<0>(pos_port), std::get<1>(pos_port));
        init_levels_sprites();
        updateEntitiesFirstConnexion(entities);
        _in_menu = false;
    }
}