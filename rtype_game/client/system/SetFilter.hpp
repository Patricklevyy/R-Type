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

                void setFilter(std::unordered_map<std::type_index, std::any> &components_array, FILTER_MODE type)
                {
                    auto &shader = std::any_cast<ecs::SparseArray<Shader> &>(components_array[typeid(Shader)]);
                    shader[0].value().loadShader(type);
                }
            private:
        };
    }

#endif /* !SETFILTER_HPP_ */