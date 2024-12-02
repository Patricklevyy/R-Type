/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MessageCompressor
*/

#ifndef MESSAGECOMPRESSOR_HPP_
    #define MESSAGECOMPRESSOR_HPP_

    #include "../Includes.hpp"
    #include "../Structures.hpp"

    class MessageCompressor {
        public:
            MessageCompressor();
            ~MessageCompressor();

            void serialize(const Message& msg, std::vector<char>& buffer);
            void deserialize(const std::vector<char>& buffer, Message& msg);

        protected:
        private:
    };

#endif /* !MESSAGECOMPRESSOR_HPP_ */
