/*
** EPITECH PROJECT, 2025
** R-TYPE
** File description:
** PocExceptions
*/

#ifndef POCEXCEPTIONS_HPP_
    #define POCEXCEPTIONS_HPP_

    #include <iostream>

    namespace poc_game
    {
        namespace ERROR
        {
            /**
             * @class InvalidTpsOrFpsExceptions
             * @brief Exception thrown for invalid tps or fps .
             */
            class InvalidTpsOrFpsExceptions : public std::exception {
            public:
                explicit InvalidTpsOrFpsExceptions(const std::string &message)
                    : message_("InvalidTpsOrFpsExceptions: " + message)
                {
                }

                const char *what() const noexcept override
                {
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
             * @class MissingPortParamsExceptions
             * @brief Exception thrown for invalid actions in the game.
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
        }
    }

#endif /* !POCEXCEPTIONS_HPP_ */
