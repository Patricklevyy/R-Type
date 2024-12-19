/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** RTypeExceptions
*/

#ifndef RTYPEEXCEPTIONS_HPP_
    #define RTYPEEXCEPTIONS_HPP_

    #include <iostream>

    namespace rtype
    {
        namespace ERROR
        {
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
        }
    }
#endif /* !RTYPEEXCEPTIONS_HPP_ */
