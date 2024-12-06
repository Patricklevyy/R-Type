/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SparseArray
*/

#ifndef SPARSEARRAY_HPP_
    #define SPARSEARRAY_HPP_

    #include "Includes_ecs.hpp"
    #include <optional>
    #include <typeindex>
    #include <list>
    #include <any>

    namespace ecs
    {
        template <typename T>
        class SparseArray {
            public:
                std::optional<T>& operator[](std::size_t index) {
                    if (index >= data.size()) {
                        throw std::out_of_range("Index out of bounds");
                    }
                    return data[index];
                }

                const std::optional<T>& operator[](std::size_t index) const {
                    if (index >= data.size()) {
                        throw std::out_of_range("Index out of bounds");
                    }
                    return data[index];
                }

                void resize(std::size_t new_size) {
                    data.resize(new_size);
                }

                std::size_t size() const {
                    return data.size();
                }

                void set(std::size_t index, const T& value) {
                    if (index >= data.size()) {
                        resize(index + 1);
                    }
                    data[index] = value;
                }

                void remove(std::size_t index) {
                    if (index < data.size()) {
                        data[index].reset();
                    }
                }

                bool has(std::size_t index) const {
                    return index < data.size() && data[index].has_value();
                }

            private:
                std::vector<std::optional<T>> data;
        };
    }


#endif /* !SPARSEARRAY_HPP_ */
