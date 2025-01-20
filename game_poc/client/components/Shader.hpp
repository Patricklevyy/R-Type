/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Shader
*/

/**
 * @file Shader.hpp
 * @brief Represents a shader applied to the game for the accessibility.
 */

#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

namespace poc_game
{
    class Shader
    {
    public:
        /**
         * @brief Constructs a shader object with a specific filter type.
         *
         * @param type The filter mode for the shader.
         */
        Shader(FILTER_MODE type)
        {
            filter = std::make_shared<sf::Shader>();
            loadShader(type);
        }

        /**
         * @brief Gets the SFML shader object.
         *
         * @return Shared pointer to the SFML shader.
         */
        std::shared_ptr<sf::Shader> getShader()
        {
            return filter;
        }

        /**
         * @brief Loads the shader corresponding to the specified filter type.
         *
         * @param type The filter mode for the shader.
         * @return True if the shader was loaded successfully, false otherwise.
         */
        bool loadShader(FILTER_MODE type)
        {
            std::string path = getShaderPath(type);
            try
            {
                if (!filter->loadFromFile(path, sf::Shader::Fragment))
                {
                    throw std::runtime_error("Failed to load shader from: " + path);
                }
                return true;
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << std::endl;
                return false;
            }
        }

    private:
        std::shared_ptr<sf::Shader> filter;

        /**
         * @brief Gets the file path for a shader based on the filter mode.
         *
         * @param type The filter mode.
         * @return The file path to the corresponding shader.
         * @throws std::runtime_error If the filter mode is unknown.
         */
        std::string getShaderPath(FILTER_MODE type) const
        {
            switch (type)
            {
            case FILTER_MODE::Neutral:
                return "assets/shaders/neutral.frag";
            case FILTER_MODE::Protanopia:
                return "assets/shaders/protanopia.frag";
            case FILTER_MODE::Deuteranopia:
                return "assets/shaders/deuteranopia.frag";
            case FILTER_MODE::Tritanopia:
                return "assets/shaders/tritanopia.frag";
            case FILTER_MODE::Inverted:
                return "assets/shaders/invert.frag";
            default:
                throw std::runtime_error("Unknown filter mode");
            }
        }
    };

}

#endif /* SHADER_HPP_ */
