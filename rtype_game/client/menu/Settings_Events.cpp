/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Settings_Events
*/

#include "Settings.hpp"

namespace rtype
{
    void Settings::updateKeybindingEvent(sf::Event event)
    {
        if (event.type == sf::Event::KeyPressed
            && selectedKey != sf::Keyboard::Unknown) {
            sf::Keyboard::Key newKey = event.key.code;

            bool keyAlreadyUsed = false;
            for (const auto &binding : _bindings) {
                if (binding.second == newKey) {
                    keyAlreadyUsed = true;
                    break;
                }
            }

            if (keyAlreadyUsed) {
                std::cout << "Key " << keyToString(newKey)
                          << " is already assigned to another action!"
                          << std::endl;
            } else {
                for (auto &binding : _bindings) {
                    if (binding.first == selectedKey) {
                        binding.second = newKey;
                        break;
                    }
                }
            }

            selectedKey = sf::Keyboard::Unknown;
        }
    }

    void Settings::updateFiltersEvent(sf::Event event)
    {
        if (event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

            float panelStartY = 200;
            float filterStartY = panelStartY + 90;
            float filterSpacing = 55;

            if (mousePos.x >= 20
                && mousePos.x <= (_window.getSize().x / 2.0f - 20)) {
                int index = (mousePos.y - filterStartY) / filterSpacing;
                if (index >= 0 && index < 5) {
                    _currentFilter = static_cast<FILTER_MODE>(index);
                    _client.set_window_filter(_currentFilter);
                    std::cout << "Filter selected: "
                              << filterModeToString(_currentFilter)
                              << std::endl;
                }
            }
        }
    }

    void Settings::updateDifficultyEvent(sf::Event event)
    {
        if (event.type != sf::Event::MouseButtonPressed
            || event.mouseButton.button != sf::Mouse::Left)
            return;

        sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

        float panelStartY = 200;
        float accessibilityHeight = 400;
        float difficultyStartY = panelStartY + accessibilityHeight + 50;

        float optionStartY = difficultyStartY + 90;
        float optionSpacing = 55;

        for (size_t i = 0; i < 4; ++i) {
            float optionPosY = optionStartY + i * optionSpacing;
            sf::FloatRect optionRect(40, optionPosY, 200, 30);

            if (optionRect.contains(static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y))) {
                _currentdifficulty = static_cast<DIFFICULTY>(i);
                _client.changeDifficulty(_currentdifficulty);
                return;
            }
        }
    }

    void Settings::handleEvents(bool &inSettings)
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                inSettings = false;
                _window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed
                && selectedKey == sf::Keyboard::Unknown) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);

                float leftPanelWidth = _window.getSize().x / 2.0f;
                float panelStartY = 200 + 100;
                int index = (mousePos.y - panelStartY) / 120;
                if (index >= 0
                    && static_cast<std::size_t>(index) < _bindings.size()) {
                    float keyStartX = leftPanelWidth + 100;
                    float keyEndX =
                        keyStartX + _formerKey.getGlobalBounds().width;

                    if (mousePos.x >= keyStartX && mousePos.x <= keyEndX) {
                        auto it = std::next(_bindings.begin(), index);
                        selectedKey = it->first;
                    }
                }
            }
            updateKeybindingEvent(event);
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
                sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                    static_cast<float>(mousePos.y));

                if (_returnButton.getGlobalBounds().contains(mousePosF)) {
                    applyChanges(_client);
                    inSettings = false;
                    return;
                }
            }
            updateFiltersEvent(event);
            updateDifficultyEvent(event);
        }
    }
} // namespace rtype