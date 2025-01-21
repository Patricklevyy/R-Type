/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Settings
*/

#include "Settings.hpp"

namespace rtype
{
    Settings::Settings(sf::RenderWindow &win,
        std::map<sf::Keyboard::Key, sf::Keyboard::Key> &keyBindings,
        Client &client)
        : _window(win), _bindings(keyBindings),
          selectedKey(sf::Keyboard::Unknown),
          _currentFilter(client._currentFilter), _client(client),
          _currentdifficulty(_client._difficulty)
    {
        if (!_formerKeyTexture.loadFromFile(
                "assets/settings/former_key_bind.png")
            || !_newKeyTexture.loadFromFile("assets/settings/new_key_bind.png")
            || !_rightArrowTexture.loadFromFile(
                "assets/settings/right_arrow.png")
            || !_choosenIconTexture.loadFromFile(
                "assets/settings/choosen_icon.png")
            || !_returnButtonTexture.loadFromFile(
                "assets/settings/return_img.png")
            || !_settingsTexture.loadFromFile(
                "assets/settings/settings_background.jpg")) {
            throw std::runtime_error("Failed to load resources");
        }
        _formerKey.setTexture(_formerKeyTexture);
        _formerKey.setScale(0.8f, 0.8f);
        _newKey.setTexture(_newKeyTexture);
        _newKey.setScale(0.9f, 0.9f);
        _rightArrow.setTexture(_rightArrowTexture);
        _rightArrow.setScale(0.4f, 0.4f);
        _choosenIcon.setTexture(_choosenIconTexture);
        _choosenIcon.setScale(0.5f, 0.5f);
        _returnButton.setTexture(_returnButtonTexture);
        _returnButton.setPosition(10, 10);
        _settings.setTexture(_settingsTexture);
    }

    void Settings::render()
    {
        _window.clear(sf::Color::Black);

        sf::Font font;
        if (!font.loadFromFile("assets/fonts/komikax.ttf")) {
            return;
        }
        auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(
            _client._ecs._components_arrays.at(typeid(Shader)));
        auto leshader = shader[0].value().getShader().get();
        _window.draw(_settings, leshader);
        drawTitleAndPanels(font);
        drawAccessibilitySection(font);
        drawKeybindingsSection(font);
        drawDifficultySection(font);
        _window.draw(_returnButton, leshader);

        _window.display();
    }

    void Settings::drawTitleAndPanels(sf::Font &font)
    {
        auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(
            _client._ecs._components_arrays.at(typeid(Shader)));
        auto leshader = shader[0].value().getShader().get();
        sf::Vector2u winSize = _window.getSize();
        float leftPanelWidth = winSize.x / 2.0f;

        sf::Text settingsText;
        settingsText.setFont(font);
        settingsText.setString("SETTINGS");
        settingsText.setStyle(sf::Text::Underlined);
        settingsText.setCharacterSize(48);
        settingsText.setFillColor(sf::Color::White);
        settingsText.setPosition(
            winSize.x / 2.0f - settingsText.getGlobalBounds().width / 2.0f, 20);
        _window.draw(settingsText, leshader);

        float panelStartY = 200;

        sf::RectangleShape keybindingsRect(
            sf::Vector2f(leftPanelWidth - 40, 600));
        keybindingsRect.setPosition(leftPanelWidth + 20, panelStartY - 20);
        keybindingsRect.setFillColor(sf::Color::Transparent);
        keybindingsRect.setOutlineColor(sf::Color::Red);
        keybindingsRect.setOutlineThickness(4.f);
        _window.draw(keybindingsRect, leshader);
    }

    void Settings::drawAccessibilitySection(sf::Font &font)
    {
        sf::Vector2u winSize = _window.getSize();
        float leftPanelWidth = winSize.x / 2.0f;
        float panelStartY = 200;
        auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(
            _client._ecs._components_arrays.at(typeid(Shader)));
        auto leshader = shader[0].value().getShader().get();

        sf::RectangleShape accessibilityRect(
            sf::Vector2f(leftPanelWidth - 40, 400));
        accessibilityRect.setPosition(20, panelStartY - 20);
        accessibilityRect.setFillColor(sf::Color::Transparent);
        accessibilityRect.setOutlineColor(sf::Color::Red);
        accessibilityRect.setOutlineThickness(4.f);
        _window.draw(accessibilityRect, leshader);

        sf::Text accessibilityText;
        accessibilityText.setFont(font);
        accessibilityText.setString("ACCESSIBILITY");
        accessibilityText.setStyle(sf::Text::Underlined);
        accessibilityText.setCharacterSize(32);
        accessibilityText.setFillColor(sf::Color::White);
        accessibilityText.setPosition(leftPanelWidth / 2.0f
                - accessibilityText.getGlobalBounds().width / 2.0f,
            panelStartY);
        _window.draw(accessibilityText, leshader);

        std::vector<std::string> filterNames = {
            "Neutral", "Protanopia", "Deuteranopia", "Tritanopia", "Inverted"};
        float filterStartY = panelStartY + 90;
        float filterSpacing = 55;

        for (size_t i = 0; i < filterNames.size(); ++i) {
            sf::Text filterText;
            filterText.setFont(font);
            filterText.setString(filterNames[i]);
            filterText.setCharacterSize(24);

            float filterPosY = filterStartY + i * filterSpacing;

            if (static_cast<FILTER_MODE>(i) == _currentFilter) {
                filterText.setFillColor(sf::Color::Yellow);

                _choosenIcon.setPosition(
                    filterText.getLocalBounds().width + 80, filterPosY);
                _window.draw(_choosenIcon, leshader);
            } else {
                filterText.setFillColor(sf::Color::White);
            }

            filterText.setPosition(40, filterPosY);
            _window.draw(filterText, leshader);
        }
    }

    void Settings::drawKeybindingsSection(sf::Font &font)
    {
        sf::Vector2u winSize = _window.getSize();
        float leftPanelWidth = winSize.x / 2.0f;
        float panelStartY = 200;
        auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(
            _client._ecs._components_arrays.at(typeid(Shader)));
        auto leshader = shader[0].value().getShader().get();

        sf::Text keybindingsText;
        keybindingsText.setFont(font);
        keybindingsText.setString("KEYBINDINGS");
        keybindingsText.setStyle(sf::Text::Underlined);
        keybindingsText.setCharacterSize(32);
        keybindingsText.setFillColor(sf::Color::White);
        keybindingsText.setPosition(leftPanelWidth
                + (leftPanelWidth / 2.0f
                    - keybindingsText.getGlobalBounds().width / 2.0f),
            panelStartY);
        _window.draw(keybindingsText, leshader);

        int y = panelStartY + 100;
        for (const auto &binding : _bindings) {
            _formerKey.setPosition(leftPanelWidth + 100, y);
            sf::Text formerKeyText;
            formerKeyText.setFont(font);
            formerKeyText.setString(showDirections(keyToString(binding.first)));
            formerKeyText.setCharacterSize(24);
            formerKeyText.setFillColor(sf::Color::Black);
            formerKeyText.setPosition(_formerKey.getPosition().x
                    + (_formerKey.getGlobalBounds().width / 2.f
                        - formerKeyText.getGlobalBounds().width / 2.f),
                _formerKey.getPosition().y
                    + (_formerKey.getGlobalBounds().height / 2.f
                        - formerKeyText.getGlobalBounds().height / 2.f));
            _window.draw(_formerKey, leshader);
            _window.draw(formerKeyText, leshader);

            _rightArrow.setPosition(leftPanelWidth + 240,
                y
                    + (_formerKey.getGlobalBounds().height / 2.f
                        - _rightArrow.getGlobalBounds().height / 2.f));
            _window.draw(_rightArrow, leshader);

            _newKey.setPosition(leftPanelWidth + 340, y);
            sf::Text newKeyText;
            newKeyText.setFont(font);
            newKeyText.setString(keyToString(binding.second));
            newKeyText.setCharacterSize(24);
            newKeyText.setFillColor(sf::Color::Black);
            newKeyText.setPosition(_newKey.getPosition().x
                    + (_newKey.getGlobalBounds().width / 2.f
                        - newKeyText.getGlobalBounds().width / 2.f),
                _newKey.getPosition().y
                    + (_newKey.getGlobalBounds().height / 2.f
                        - newKeyText.getGlobalBounds().height / 2.f));
            _window.draw(_newKey, leshader);
            _window.draw(newKeyText, leshader);

            y += 120;
        }
    }

    void Settings::drawDifficultySection(sf::Font &font)
    {
        sf::Vector2u winSize = _window.getSize();
        float leftPanelWidth = winSize.x / 2.0f;

        float accessibilityHeight = 400;
        float panelStartY = 200;
        float difficultyStartY = panelStartY + accessibilityHeight + 50;

        auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(
            _client._ecs._components_arrays.at(typeid(Shader)));
        auto leshader = shader[0].value().getShader().get();

        sf::RectangleShape difficultyRect(
            sf::Vector2f(leftPanelWidth - 40, 400));
        difficultyRect.setPosition(20, difficultyStartY - 20);
        difficultyRect.setFillColor(sf::Color::Transparent);
        difficultyRect.setOutlineColor(sf::Color::Red);
        difficultyRect.setOutlineThickness(4.f);
        _window.draw(difficultyRect, leshader);

        sf::Text difficultyText;
        difficultyText.setFont(font);
        difficultyText.setString("DIFFICULTY LEVEL");
        difficultyText.setStyle(sf::Text::Underlined);
        difficultyText.setCharacterSize(32);
        difficultyText.setFillColor(sf::Color::White);
        difficultyText.setPosition(leftPanelWidth / 2.0f
                - difficultyText.getGlobalBounds().width / 2.0f,
            difficultyStartY);
        _window.draw(difficultyText, leshader);

        std::vector<std::string> difficultyNames = {
            "EASY", "MEDIUM", "HARD", "IMPOSSIBLE"};
        float optionStartY = difficultyStartY + 90;
        float optionSpacing = 55;

        for (size_t i = 0; i < difficultyNames.size(); ++i) {
            sf::Text difficultyOptionText;
            difficultyOptionText.setFont(font);
            difficultyOptionText.setString(difficultyNames[i]);
            difficultyOptionText.setCharacterSize(24);

            float optionPosY = optionStartY + i * optionSpacing;

            if (static_cast<DIFFICULTY>(i) == _currentdifficulty) {
                difficultyOptionText.setFillColor(sf::Color::Yellow);

                _choosenIcon.setPosition(
                    difficultyOptionText.getLocalBounds().width + 80,
                    optionPosY);
                _window.draw(_choosenIcon, leshader);
            } else {
                difficultyOptionText.setFillColor(sf::Color::White);
            }

            difficultyOptionText.setPosition(40, optionPosY);
            _window.draw(difficultyOptionText, leshader);
        }
    }

    void Settings::run(bool &inSettings)
    {
        while (inSettings) {
            handleEvents(inSettings);
            render();
        }
    }
} // namespace rtype
