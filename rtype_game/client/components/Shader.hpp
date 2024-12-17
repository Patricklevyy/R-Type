#ifndef SHADER_HPP_
#define SHADER_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>
#include <stdexcept>
#include <string>

namespace rtype
{
    class Shader
    {
    public:
        Shader(FILTER_MODE type)
        {
            filter = std::make_shared<sf::Shader>();
            loadShader(type);
        }

        std::shared_ptr<sf::Shader> getShader()
        {
            return filter;
        }

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
