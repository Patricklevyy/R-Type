/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "../Client.hpp"

namespace rtype
{
    class Client;
    class Settings {
      public:
        Settings(sf::RenderWindow &win,
            std::map<sf::Keyboard::Key, sf::Keyboard::Key> &, Client&);
        ~Settings() {};
        void run(bool &inSettings);
        void render();
        void handleEvents(bool &inSettings);
        std::string keyToString(sf::Keyboard::Key key);
        std::string showDirections(std::string);
        void drawTitleAndPanels(sf::Font &font);
        void drawAccessibilitySection(sf::Font &font);
        void drawKeybindingsSection(sf::Font &font);
        std::string filterModeToString(FILTER_MODE mode);
        void applyChanges(Client &client);
        void updateKeybindingEvent(sf::Event);
        void updateFiltersEvent(sf::Event);


      protected:
      private:
        sf::RenderWindow &_window;
        std::map<sf::Keyboard::Key, sf::Keyboard::Key> &_bindings;
        sf::Sprite _formerKey;
        sf::Texture _formerKeyTexture;

        sf::Sprite _newKey;
        sf::Texture _newKeyTexture;

        sf::Sprite _settings;
        sf::Texture _settingsTexture;

        sf::Sprite _rightArrow;
        sf::Texture _rightArrowTexture;
        sf::Sprite _choosenIcon;
        sf::Texture _choosenIconTexture;
        sf::Keyboard::Key selectedKey;
        sf::Sprite _returnButton;
        sf::Texture _returnButtonTexture;
        FILTER_MODE _currentFilter = FILTER_MODE::Neutral;
        Client &_client;
    };
} // namespace rtype

#endif /* !SETTINGS_HPP_ */
