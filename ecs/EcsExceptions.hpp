/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EcsExceptions
*/

#ifndef ECSEXCEPTIONS_HPP_
    #define ECSEXCEPTIONS_HPP_

    #include <iostream>

    namespace ecs
    {
        namespace ERROR
        {
            class CantReadConfigFileExceptions : virtual public std::exception
            {
            public:
                CantReadConfigFileExceptions() {}

                const char *what() const noexcept override
                {
                    return ("CantReadConfigFileExceptions : Error when reading the config file");
                };
            };

            class CantParseConfigFileExceptions : virtual public std::exception
            {
            public:
                CantParseConfigFileExceptions() {}

                const char *what() const noexcept override
                {
                    return ("CantParseConfigFileExceptions : Error parsing configuration file");
                };
            };

            class WrongBufferSizeExceptions : virtual public std::exception
            {
            public:
                WrongBufferSizeExceptions() {}

                const char *what() const noexcept override
                {
                    return ("WrongBufferSizeExceptions : Buffer size exceeds safe UDP message size (1472 bytes).");
                };
            };

            class BindFailedExceptions : virtual public std::exception
            {
            public:
                BindFailedExceptions() {}

                const char *what() const noexcept override
                {
                    return ("BindFailedExceptions : Bind failed.");
                };
            };

            class WrongConfigurationExceptions : virtual public std::exception
            {
            public:
                WrongConfigurationExceptions() {}

                const char *what() const noexcept override
                {
                    return ("WrongConfigurationExceptions : Missing setting or wrong setting in configuration file.");
                };
            };

            class SocketNotInitializedExceptions : virtual public std::exception
            {
            public:
                SocketNotInitializedExceptions() {}

                const char *what() const noexcept override
                {
                    return ("SocketNotInitializedExceptions : Socket not initialized.");
                };
            };

            class InvalidAdressFormatExceptions : virtual public std::exception
            {
            public:
                InvalidAdressFormatExceptions() {}

                const char *what() const noexcept override
                {
                    return ("InvalidAdressFormatExceptions : Invalid address format. Expected 'ip:port'.");
                };
            };

            class InvalidIpAdressExceptions : virtual public std::exception
            {
            public:
                InvalidIpAdressExceptions() {}

                const char *what() const noexcept override
                {
                    return ("InvalidIpAdressExceptions : Invalid IP address.");
                };
            };

            class MessageTooBigExceptions : virtual public std::exception
            {
            public:
                MessageTooBigExceptions() {}

                const char *what() const noexcept override
                {
                    return ("MessageTooBigExceptions : Message exceeds buffer size.");
                };
            };

            class RecvExceptions : virtual public std::exception
            {
            public:
                RecvExceptions() {}

                const char *what() const noexcept override
                {
                    return ("RecvExceptions : Recvfrom failed.");
                };
            };
            class ComponentTypeAlreadyExistException : virtual public std::exception
            {
            public:
                ComponentTypeAlreadyExistException() {}

                const char *what() const noexcept override
                {
                    return ("ComponentTypeAlreadyExistException : Component already exists.");
                };
            };

            class ComponentNotFoundExceptions : virtual public std::exception
            {
            public:
                ComponentNotFoundExceptions() {}

                const char *what() const noexcept override
                {
                    return ("ComponentNotFoundExceptions : Component not found.");
                };
            };

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
