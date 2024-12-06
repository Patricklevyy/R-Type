/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MessageCompressor
*/

#ifndef MESSAGECOMPRESSOR_HPP_
    #define MESSAGECOMPRESSOR_HPP_

    #include "../Includes_ecs.hpp"
    #include "../Structures_ecs.hpp"

    namespace ecs
    {
        namespace udp
        {
            class MessageCompressor {
                public:
                    MessageCompressor();
                    ~MessageCompressor();

                    void serialize(const Message& msg, std::vector<char>& buffer);
                    void deserialize(const std::vector<char>& buffer, Message& msg);

                protected:
                private:
            };
        }
    }

#endif /* !MESSAGECOMPRESSOR_HPP_ */
