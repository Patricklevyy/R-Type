/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SetFilter
*/

/**
 * @file SetFilter.hpp
 * @brief Manages the application of graphical filters (shaders) to game elements.
 */

#ifndef SETFILTER_HPP_
    #define SETFILTER_HPP_

    #include "../components/Window.hpp"
    #include "../components/Background.hpp"
    #include "../components/Shader.hpp"
    #include "../../shared/Includes.hpp"
    #include <iostream>
    #include "../../../ecs/SparseArray.hpp"
    #include "../components/Displayable.hpp"
    #include "../../../ecs/components/Position.hpp"

    namespace rtype
    {
        class SetFilter
        {
            public:

                /**
                 * @brief Applies a graphical filter to the specified components.
                 *
                 * This method uses a shader to apply a visual effect corresponding to the given filter type.
                 *
                 * @param components_array The ECS component map that contains all components.
                 * @param type The filter mode to apply (e.g., Neutral, Protanopia, Deuteranopia, etc.).
                 */
                void setFilter(std::unordered_map<std::type_index, std::any> &components_array, FILTER_MODE type)
                {
                    auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(components_array[typeid(Shader)]);
                    shader[0].value().loadShader(type);
                }
            private:
        };
    }

#endif /* !SETFILTER_HPP_ */