/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Manager
*/

#ifndef UDP_MANAGER_HPP
    #define UDP_MANAGER_HPP

    #include "../Includes.hpp"

    namespace ecs
    {
        namespace udp
        {
            /**
             * @class UDP_Manager
             * @brief Cette UDP manager gère les messages de première connexion d'un client
             *
             */
            class UDP_Manager {
                public:
                    /**
                     * @brief Constructeur par défaut.
                     */
                    UDP_Manager();
                    virtual ~UDP_Manager();

                     /**
                     * @brief Initialize le port du server et ecoute sur le port defini par le config file
                     * @param configFile Un config file qui set le port et l'ip
                     * @param port Cet argument n'est pas utilisé par cette udp
                     * @return Retourne true si l'initialisation s'est bien passé
                     */
                    virtual bool initialize(const std::string& configFile, int port = 0);

                    /**
                     * @brief Send un message a l'addresse du client donné en param
                     * @param message Message serialisé par le message compressor
                     * @param address Address du receiver
                     * @return Retourne true si l'envoie s'est bien passé
                     */
                    virtual bool sendMessage(const std::vector<char>& message, const std::string &address);

                    /**
                     * @brief Recois un message et le met dans std::vector<char>& message
                     * @param message std::vector vide car il va ếtre intialisé par le message
                     * @return Retourne true si la reception s'est bien passé
                     */
                    virtual bool receiveMessage(std::vector<char>& message);

                    /**
                     * @brief Retourne l'addresse du dernier client qui a envoyé un message
                     * @return Retourne l'addresse du dernier client
                     */
                    virtual std::string getLastClientAddress() const;

                protected:
                    int sockfd;
                    int bufferSize;
                    sockaddr_in serverAddr;
                    sockaddr_in lastSenderAddr;
                    bool lastSenderValid;
                    std::string clientAddrStr;
                };
        }
    }

#endif // UDP_MANAGER_HPP