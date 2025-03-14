/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

#include "UDP_Manager.hpp"

namespace ecs
{
    namespace udp
    {
        UDP_Manager::UDP_Manager()
            : sockfd(-1), bufferSize(1472), lastSenderValid(false)
        {
        }

        UDP_Manager::~UDP_Manager()
        {
            if (sockfd >= 0)
                close(sockfd);
        }

        bool UDP_Manager::initialize(const std::string &configFile, int port)
        {
            (void) port;
            libconfig::Config cfg;

            try {
                std::cout << configFile.c_str() << std::endl;
                cfg.readFile(configFile.c_str());
            } catch (const libconfig::FileIOException &e) {
                throw ecs::ERROR::CantReadConfigFileExceptions();
            } catch (const libconfig::ParseException &e) {
                throw ecs::ERROR::CantParseConfigFileExceptions();
            }

            const libconfig::Setting &root = cfg.getRoot();

            try {
                const libconfig::Setting &udpSettings = root["UDP"];
                bufferSize = udpSettings["buffer_size"];

                if (udpSettings.exists("secrete_key_rtype")) {
                    secret_key = udpSettings["secrete_key_rtype"].c_str();
                } else {
                    throw ecs::ERROR::MissingSecretKeyInConfigFileException(
                        "Missing key");
                }

                if (bufferSize > 1472) {
                    throw ecs::ERROR::WrongBufferSizeExceptions();
                }

                sockaddr_in addr{};
                addr.sin_family = AF_INET;

                const libconfig::Setting &serverSettings =
                    udpSettings["server"];
                std::string ip = serverSettings["ip"];
                int port_config = serverSettings["port"];
                addr.sin_port = htons(port_config);
                inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

                sockfd = socket(AF_INET, SOCK_DGRAM, 0);
                if (sockfd < 0) {
                    throw ecs::ERROR::SocketNotInitializedExceptions();
                }
                int flags = fcntl(sockfd, F_GETFL, 0);
                if (flags < 0
                    || fcntl(sockfd, F_SETFL, flags | O_NONBLOCK) < 0) {
                    close(sockfd);
                    sockfd = -1;
                    throw ecs::ERROR::SocketNotInitializedExceptions();
                }

                if (bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
                    close(sockfd);
                    sockfd = -1;
                    throw ecs::ERROR::BindFailedExceptions();
                }

                std::cout << "Server is running on " << ip << ":" << port_config
                          << "\n";
            } catch (const libconfig::SettingNotFoundException &e) {
                throw ecs::ERROR::WrongConfigurationExceptions();
            } catch (const libconfig::SettingTypeException &e) {
                throw ecs::ERROR::WrongConfigurationExceptions();
            }

            return true;
        }

        void UDP_Manager::startReceiving()
        {
            isRunning = true;
            receiverThread = std::thread(&UDP_Manager::receiveLoop, this);
        }

        void UDP_Manager::stopReceiving()
        {
            isRunning = false;
            if (receiverThread.joinable())
                receiverThread.join();
        }

        void UDP_Manager::receiveLoop()
        {
            while (isRunning) {
                std::vector<char> message;
                if (receiveMessage(message)) {
                    enqueueMessage(message, getLastClientAddress());
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }

        bool UDP_Manager::receiveMessage(std::vector<char> &message)
        {
            char buffer[bufferSize];
            sockaddr_in senderAddr{};
            socklen_t senderLen = sizeof(senderAddr);

            ssize_t received = recvfrom(sockfd, buffer, bufferSize, 0,
                (struct sockaddr *) &senderAddr, &senderLen);
            if (received < 0) {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    return false;
                throw ecs::ERROR::RecvExceptions();
            }

            message.assign(buffer, buffer + received);
            lastSenderAddr = senderAddr;
            lastSenderValid = true;
            clientAddrStr = std::string(inet_ntoa(senderAddr.sin_addr)) + ":"
                + std::to_string(ntohs(senderAddr.sin_port));
            return true;
        }

        void UDP_Manager::enqueueMessage(
            const std::vector<char> &message, const std::string &clientAddress)
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            messageQueue.emplace(clientAddress, message);
            queueCondition.notify_one();
        }

        std::vector<std::pair<std::string, std::vector<char>>>
        UDP_Manager::fetchAllMessages()
        {
            std::vector<std::pair<std::string, std::vector<char>>> messages;
            std::lock_guard<std::mutex> lock(queueMutex);

            while (!messageQueue.empty()) {
                messages.push_back(messageQueue.front());
                messageQueue.pop();
            }
            return messages;
        }

        std::string UDP_Manager::getLastClientAddress() const
        {
            return clientAddrStr;
        }

        bool UDP_Manager::sendMessage(
            const std::vector<char> &message, const std::string &address)
        {
            // std::cerr << "[DEBUG] sendMessage called with address: " <<
            // address << std::endl;

            size_t colonPos = address.find(':');
            if (colonPos == std::string::npos) {
                std::cerr << "[ERROR] Invalid address format: " << address
                          << std::endl;
                throw ecs::ERROR::InvalidAdressFormatExceptions();
            }

            std::string ip = address.substr(0, colonPos);
            int port = std::stoi(address.substr(colonPos + 1));

            // std::cerr << "[DEBUG] Parsed IP: " << ip << ", Port: " << port <<
            // std::endl;

            sockaddr_in receiverAddr{};
            receiverAddr.sin_family = AF_INET;
            receiverAddr.sin_port = htons(port);
            if (inet_pton(AF_INET, ip.c_str(), &receiverAddr.sin_addr) <= 0) {
                std::cerr << "[ERROR] Failed to parse IP address: " << ip
                          << std::endl;
                throw ecs::ERROR::InvalidAdressFormatExceptions();
            }
            if (message.size() > bufferSize) {
                std::cerr << "[ERROR] Message size exceeds buffer size: "
                          << message.size() << " > " << bufferSize << std::endl;
                throw ecs::ERROR::MessageTooBigExceptions();
            }

            if (sockfd < 0) {
                std::cerr << "[ERROR] Socket is not initialized correctly!"
                          << std::endl;
                return false;
            }

            // std::cerr << "[DEBUG] Sending message of size: " <<
            // message.size() << std::endl;

            ssize_t sent = sendto(sockfd, message.data(), message.size(), 0,
                (struct sockaddr *) &receiverAddr, sizeof(receiverAddr));
            if (sent < 0) {
                std::cerr << "[ERROR] sendto failed: " << strerror(errno)
                          << std::endl;
                return false;
            }
            return true;
        }

        std::string UDP_Manager::getSecretKey() const
        {
            return secret_key;
        }

    } // namespace udp
} // namespace ecs