/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RTypeExceptions
*/

/**
 * @file RTypeExceptions.hpp
 * @brief Defines custom exception classes for error handling in the R-Type game.
 */

#ifndef RTYPEEXCEPTIONS_HPP_
    #define RTYPEEXCEPTIONS_HPP_

    #include <iostream>

    namespace rtype
    {
        namespace ERROR
        {
            /**
             * @class InvalidActionExceptions
             * @brief Exception thrown for invalid actions in the game.
             */
            class InvalidActionExceptions : public std::exception {
                public:
                    explicit InvalidActionExceptions(const std::string& message)
                        : message_("InvalidActionExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class WrongFormatParamsExceptions
             * @brief Exception thrown for incorrect parameter formats.
             */
            class WrongFormatParamsExceptions : public std::exception {
                public:
                    explicit WrongFormatParamsExceptions(const std::string& message)
                        : message_("WrongFormatParamsExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class MissingRoomsParamsExceptions
             * @brief Exception thrown for missing romms parameter.
             */
            class MissingRoomsParamsExceptions : public std::exception {
                public:
                    explicit MissingRoomsParamsExceptions(const std::string& message)
                        : message_("MissingRoomsParamsExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class RoomAlreadyExistingExceptions
             * @brief Exception thrown for already existing room.
             */
            class RoomAlreadyExistingExceptions : public std::exception {
                public:
                    explicit RoomAlreadyExistingExceptions(const std::string& message)
                        : message_("RoomAlreadyExistingExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class RoomNotFoundExceptions
             * @brief Exception thrown for not found room.
             */
            class RoomNotFoundExceptions : public std::exception {
                public:
                    explicit RoomNotFoundExceptions(const std::string& message)
                        : message_("RoomNotFoundExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class RoomIsFullExceptions
             * @brief Exception thrown when the room is full.
             */
            class RoomIsFullExceptions : public std::exception {
                public:
                    explicit RoomIsFullExceptions(const std::string& message)
                        : message_("RoomIsFullExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class InvalidTpsOrFpsExceptions
             * @brief Exception thrown for invalid tps or fps .
             */
            class InvalidTpsOrFpsExceptions : public std::exception {
                public:
                    explicit InvalidTpsOrFpsExceptions(const std::string& message)
                        : message_("InvalidTpsOrFpsExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class FailedToInitializeServerExceptions
             * @brief Exception thrown when failing to initialize the server.
             */
            class FailedToInitializeServerExceptions : public std::exception {
                public:
                    explicit FailedToInitializeServerExceptions(const std::string& message)
                        : message_("FailedToInitializeServerExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class FailedToInitializeClientExceptions
             * @brief Exception thrown when failing to initialize the server.
             */
            class FailedToInitializeClientExceptions : public std::exception {
                public:
                    explicit FailedToInitializeClientExceptions(const std::string& message)
                        : message_("FailedToInitializeClientExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class MissingPortParamsExceptions
             * @brief Exception thrown when the port params is missing.
             */
            class MissingPortParamsExceptions : public std::exception {
                public:
                    explicit MissingPortParamsExceptions(const std::string& message)
                        : message_("MissingPortParamsExceptions: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            /**
             * @class MessageIsNotSafeException
             * @brief Exception thrown when the message is not safe.
             */
            class MessageIsNotSafeException : public std::exception {
                public:
                    explicit MessageIsNotSafeException(const std::string& message)
                        : message_("MessageIsNotSafeException: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };

            class PlayerDontExistInEcsException : public std::exception {
                public:
                    explicit PlayerDontExistInEcsException(const std::string& message)
                        : message_("PlayerDontExistInEcsException: " + message) {}

                    const char* what() const noexcept override {
                        return message_.c_str();
                    }

                private:
                    std::string message_;
            };
        }
    }
#endif /* !RTYPEEXCEPTIONS_HPP_ */
