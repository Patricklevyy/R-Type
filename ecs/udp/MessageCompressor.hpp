/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** MessageCompressor
*/

/**
 * @file MessageCompressor.hpp
 * @brief Provides serialization and deserialization of UDP messages for network communication.
 */

#ifndef MESSAGECOMPRESSOR_HPP_
    #define MESSAGECOMPRESSOR_HPP_

    #include "../Includes_ecs.hpp"
    #include "../Structures_ecs.hpp"

    namespace ecs
    {
        namespace udp
        {
            /**
             * @class MessageCompressor
             * @brief Handles serialization and deserialization of messages for network transmission.
             */
            class MessageCompressor
            {
            public:
                /**
                 * @brief Default constructor for the MessageCompressor.
                 */
                MessageCompressor();
                /**
                 * @brief Default destructor for the MessageCompressor.
                 */
                ~MessageCompressor();

                /**
                 * @brief Serializes a Message into a byte buffer.
                 * @param msg The message to serialize.
                 * @param buffer The output buffer to store serialized data.
                 */
                void serialize(const Message &msg, std::vector<char> &buffer);

                /**
                 * @brief Deserializes a byte buffer into a Message object.
                 * @param buffer The input buffer containing serialized data.
                 * @param msg The output message object to populate.
                 */
                void deserialize(const std::vector<char> &buffer, Message &msg);

            protected:
            private:
            };
        }
    }

#endif /* !MESSAGECOMPRESSOR_HPP_ */
