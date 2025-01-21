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
    /**
     * @class Settings
     * @brief Manages user settings.
     */
    class Settings {
      public:
      /**
       * @brief Constructor for the Settings class.
       * @param win The window in wich we want to display the settings param.
       * @param client The map with the keybinding, to modify it if needed.
       */
        Settings(sf::RenderWindow &win,
            std::map<sf::Keyboard::Key, sf::Keyboard::Key> &, Client&);

      /**
       * @brief Destructor for the Settings class.
       */
        ~Settings() {};

      /**
       * @brief Handle and run the settings window.
       * @param inSettings States if the player is in the settings or not.
       */
        void run(bool &inSettings);

      /**
       * @brief Render the settings window.
       */
        void render();

      /**
       * @brief Manages user inputs and interactions within a specific screen.
       * @param inSettings States if the player is in the settings or not.
       */
        void handleEvents(bool &inSettings);

      /**
       * @brief Manage the Keybinding modification when the user click on the keyboard.
       * @param key The key pressed by the user.
       */
        std::string keyToString(sf::Keyboard::Key key);

      /**
       * @brief Says wich direction the user change when modifiyng keybinding parameter.
       * @param string The Direction that correspond to the key
       */
        std::string showDirections(std::string);

      /**
       * @brief Draw everything around the keybinding to make is comprehensible.
       * @param font The font that will be use to draw the explainations.
       */
        void drawTitleAndPanels(sf::Font &font);

      /**
       * @brief Handle the Accessibility parameter section.
       * @param font The font that will be use to draw the explainations.
       */
        void drawAccessibilitySection(sf::Font &font);

      /**
       * @brief Display the keybinding section in the parameter.
       * @param The font that will be use to draw the explainations.
       */
        void drawKeybindingsSection(sf::Font &font);

      /**
       * @brief Manages user inputs and interactions within a specific screen.
       * @param mode The mode of filter to use for visual accessibility.
       */
        std::string filterModeToString(FILTER_MODE mode);

      /**
       * @brief Handle all the changes that have been made and apply them.
       * @param client The client that modify parameter.
       */
        void applyChanges(Client &client);

      /**
       * @brief Update the keybinding event in parameter.
       * @param event The key pressed to replace an action.
       */
        void updateKeybindingEvent(sf::Event);

      /**
       * @brief Apply the filter selected by the user.
       * @param event The filter selected by the user.
       */
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
