/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Client
*/

#include "UDP_Client.hpp"

UDP_Client::UDP_Client()
{
}

UDP_Client::~UDP_Client()
{
}

bool UDP_Client::initialize(const std::string &configFile, int port)
{
    libconfig::Config cfg;

    try
    {
        std::cout << configFile.c_str() << std::endl;
        cfg.readFile(configFile.c_str());
    }
    catch (const libconfig::FileIOException &e)
    {
        std::cerr << "Error reading configuration file: " << e.what() << std::endl;
        return false;
    }
    catch (const libconfig::ParseException &e)
    {
        std::cerr << "Error parsing configuration file: " << e.getError() << std::endl;
        return false;
    }

    const libconfig::Setting &root = cfg.getRoot();

    try
    {
        // Obtenir les paramètres UDP
        const libconfig::Setting &udpSettings = root["UDP"];
        bufferSize = udpSettings["buffer_size"];

        // Vérifier la taille du buffer
        if (bufferSize > 1472)
        {
            std::cerr << "Buffer size exceeds safe UDP message size (1472 bytes).\n";
            return false;
        }

        sockaddr_in addr{};
        addr.sin_family = AF_INET;

        // Configuration pour le client
        const libconfig::Setting &clientSettings = udpSettings["client"];
        std::string ip = clientSettings["ip"];
        int port = clientSettings["port"];
        addr.sin_port = htons(port);
        inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);

        // Stocker l'adresse du serveur
        const libconfig::Setting &serverSettings = udpSettings["server"];
        std::string serverIp = serverSettings["ip"];
        int serverPort = serverSettings["port"];
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(serverPort);
        inet_pton(AF_INET, serverIp.c_str(), &serverAddr.sin_addr);

        sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (sockfd < 0)
        {
            perror("Socket creation failed");
            return false;
        }

        std::cout << "Client initialized to connect to " << serverIp << ":" << serverPort << "\n";
    }
    catch (const libconfig::SettingNotFoundException &e)
    {
        std::cerr << "Missing setting in configuration file: " << e.what() << "\n";
        return false;
    }
    catch (const libconfig::SettingTypeException &e)
    {
        std::cerr << "Type mismatch in configuration file: " << e.what() << "\n";
        return false;
    }

    return true;
}