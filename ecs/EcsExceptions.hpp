/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EcsExceptions
*/

/**
 * @file EcsExceptions.hpp
 * @brief Defines custom exception classes for the ECS system.
 * @details This file contains the definition of various exceptions used in the ECS system,
 *          such as configuration file errors, network issues, and invalid operations.
 */

#ifndef ECSEXCEPTIONS_HPP_
    #define ECSEXCEPTIONS_HPP_

    #include <iostream>

    namespace ecs
    {
        namespace ERROR
        {
            /**
             * @brief Exception for errors reading the configuration file.
             */
            class CantReadConfigFileExceptions : virtual public std::exception
            {
            public:
                CantReadConfigFileExceptions() {}

                const char *what() const noexcept override
                {
                    return ("CantReadConfigFileExceptions : Error when reading the config file");
                };
            };

            /**
             * @brief Exception for errors parsing the configuration file.
             */
            class CantParseConfigFileExceptions : virtual public std::exception
            {
            public:
                CantParseConfigFileExceptions() {}

                const char *what() const noexcept override
                {
                    return ("CantParseConfigFileExceptions : Error parsing configuration file");
                };
            };

            /**
            * @brief Exception for buffer size exceeding safe UDP message size.
            */
            class WrongBufferSizeExceptions : virtual public std::exception
            {
            public:
                WrongBufferSizeExceptions() {}

                const char *what() const noexcept override
                {
                    return ("WrongBufferSizeExceptions : Buffer size exceeds safe UDP message size (1472 bytes).");
                };
            };

            /**
            * @brief Exception for failed socket binding.
            */
            class BindFailedExceptions : virtual public std::exception
            {
            public:
                BindFailedExceptions() {}

                const char *what() const noexcept override
                {
                    return ("BindFailedExceptions : Bind failed.");
                };
            };

            /**
             * @brief Exception for incorrect or missing configuration settings.
             */
            class WrongConfigurationExceptions : virtual public std::exception
            {
            public:
                WrongConfigurationExceptions() {}

                const char *what() const noexcept override
                {
                    return ("WrongConfigurationExceptions : Missing setting or wrong setting in configuration file.");
                };
            };

            /**
            * @brief Exception for uninitialized socket operations.
            */
            class SocketNotInitializedExceptions : virtual public std::exception
            {
            public:
                SocketNotInitializedExceptions() {}

                const char *what() const noexcept override
                {
                    return ("SocketNotInitializedExceptions : Socket not initialized.");
                };
            };

            /**
             * @brief Exception for invalid address format.
             */
            class InvalidAdressFormatExceptions : virtual public std::exception
            {
            public:
                InvalidAdressFormatExceptions() {}

                const char *what() const noexcept override
                {
                    return ("InvalidAdressFormatExceptions : Invalid address format. Expected 'ip:port'.");
                };
            };

            /**
             * @brief Exception for invalid IP addresses.
             */
            class InvalidIpAdressExceptions : virtual public std::exception
            {
            public:
                InvalidIpAdressExceptions() {}

                const char *what() const noexcept override
                {
                    return ("InvalidIpAdressExceptions : Invalid IP address.");
                };
            };

            /**
             * @brief Exception for messages exceeding buffer size.
             */
            class MessageTooBigExceptions : virtual public std::exception
            {
            public:
                MessageTooBigExceptions() {}

                const char *what() const noexcept override
                {
                    return ("MessageTooBigExceptions : Message exceeds buffer size.");
                };
            };

            /**
             * @brief Exception for failed reception of data.
             */
            class RecvExceptions : virtual public std::exception
            {
            public:
                RecvExceptions() {}

                const char *what() const noexcept override
                {
                    return ("RecvExceptions : Recvfrom failed.");
                };
            };

            /**
            * @brief Exception for duplicate component types.
            */
            class ComponentTypeAlreadyExistException : virtual public std::exception
            {
            public:
                ComponentTypeAlreadyExistException() {}

                const char *what() const noexcept override
                {
                    return ("ComponentTypeAlreadyExistException : Component already exists.");
                };
            };

            /**
             * @brief Exception for missing components.
             */
            class ComponentNotFoundExceptions : virtual public std::exception
            {
            public:
                ComponentNotFoundExceptions() {}

                const char *what() const noexcept override
                {
                    return ("ComponentNotFoundExceptions : Component not found.");
                };
            };

            /**
            * @brief Exception for out-of-range entity IDs.
            */
            class IdOutOfRangeExceptions : virtual public std::exception
            {
            public:
                IdOutOfRangeExceptions() {}

                const char *what() const noexcept override
                {
                    return ("IdOutOfRangeExceptions : Id index out of range.");
                };
            };
        }
    }
#endif /* !ECSEXCEPTIONS_HPP_ */
