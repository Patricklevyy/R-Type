/*
** EPITECH PROJECT, 2025
** R-Type
** File description:
** Settings_Utils
*/

#include "Settings.hpp"

namespace rtype
{
    void Settings::applyChanges(Client &client)
    {
        client._sfml_handler->updateKeyBindings(_bindings);
        client._currentFilter = _currentFilter;
    }

    std::string Settings::showDirections(std::string letter)
    {
        if (letter == "Z")
            return "UP";
        if (letter == "S")
            return "DOWN";
        if (letter == "Q")
            return "LEFT";
        if (letter == "D")
            return "RIGHT";
        return nullptr;
    }

    std::string Settings::keyToString(sf::Keyboard::Key key)
    {
        switch (key) {
            case sf::Keyboard::A: return "A";
            case sf::Keyboard::B: return "B";
            case sf::Keyboard::C: return "C";
            case sf::Keyboard::D: return "D";
            case sf::Keyboard::E: return "E";
            case sf::Keyboard::F: return "F";
            case sf::Keyboard::G: return "G";
            case sf::Keyboard::H: return "H";
            case sf::Keyboard::I: return "I";
            case sf::Keyboard::J: return "J";
            case sf::Keyboard::K: return "K";
            case sf::Keyboard::L: return "L";
            case sf::Keyboard::M: return "M";
            case sf::Keyboard::N: return "N";
            case sf::Keyboard::O: return "O";
            case sf::Keyboard::P: return "P";
            case sf::Keyboard::Q: return "Q";
            case sf::Keyboard::R: return "R";
            case sf::Keyboard::S: return "S";
            case sf::Keyboard::T: return "T";
            case sf::Keyboard::U: return "U";
            case sf::Keyboard::V: return "V";
            case sf::Keyboard::W: return "W";
            case sf::Keyboard::X: return "X";
            case sf::Keyboard::Y: return "Y";
            case sf::Keyboard::Z: return "Z";

            case sf::Keyboard::Space: return "Space";
            case sf::Keyboard::Enter: return "Enter";
            case sf::Keyboard::Escape: return "Escape";
            case sf::Keyboard::LShift: return "LShift";
            case sf::Keyboard::RShift: return "RShift";
            case sf::Keyboard::LControl: return "LControl";
            case sf::Keyboard::RControl: return "RControl";
            case sf::Keyboard::LAlt: return "LAlt";
            case sf::Keyboard::RAlt: return "RAlt";

            default: return "XXX";
        }
    }

    std::string Settings::filterModeToString(FILTER_MODE mode)
    {
        switch (mode) {
            case Neutral: return "Neutral";
            case Protanopia: return "Protanopia";
            case Deuteranopia: return "Deuteranopia";
            case Tritanopia: return "Tritanopia";
            case Inverted: return "Inverted";
            default: return "XXX";
        }
    }
}