/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SparseArray
*/

/**
 * @file SparseArray.hpp
 * @brief Defines a sparse array template for efficient data storage.
 * @details The SparseArray template provides a container that allows for optional values,
 *          resizing, and efficient access based on indices.
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
        /**
        * @brief SparseArray template class.
        * @tparam T The type of elements stored in the array.
        */
        template <typename T>
        class SparseArray
        {
        public:
            /**
             * @brief Access an element by its index.
             * @param index The index to access.
             * @return A reference to the optional element.
             * @throw std::out_of_range if the index is out of bounds.
             */
            std::optional<T> &operator[](std::size_t index)
            {
                if (index >= data.size())
                {
                    throw std::out_of_range("Index out of bounds");
                }
                return data[index];
            }

            /**
             * @brief Access an element by its index (const version).
             * @param index The index to access.
             * @return A const reference to the optional element.
             * @throw std::out_of_range if the index is out of bounds.
             */
            const std::optional<T> &operator[](std::size_t index) const
            {
                if (index >= data.size())
                {
                    throw std::out_of_range("Index out of bounds");
                }
                return data[index];
            }

            /**
             * @brief Resize the array.
             * @param new_size The new size of the array.
             */
            void resize(std::size_t new_size)
            {
                data.resize(new_size);
            }

            /**
             * @brief Get the current size of the array.
             * @return The size of the array.
             */
            std::size_t size() const
            {
                return data.size();
            }

            /**
             * @brief Set a value at the specified index.
             * @param index The index to set the value at.
             * @param value The value to set.
             */
            void set(std::size_t index, const T &value)
            {
                if (index >= data.size())
                {
                    resize(index + 1);
                }
                data[index] = value;
            }

            /**
             * @brief Remove a value at the specified index.
             * @param index The index to remove the value from.
             */
            void remove(std::size_t index)
            {
                if (index < data.size())
                {
                    data[index].reset();
                }
            }

            /**
            * @brief Check if an index has a value.
            * @param index The index to check.
            * @return True if the index has a value, false otherwise.
            */
            bool has(std::size_t index) const
            {
                return index < data.size() && data[index].has_value();
            }

        private:
            std::vector<std::optional<T>> data;  ///< Storage for the sparse array elements.
        };
    }

#endif /* !SPARSEARRAY_HPP_ */
