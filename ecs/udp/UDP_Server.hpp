/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** UDP_Server
*/

#ifndef UDP_SERVER_HPP
    #define UDP_SERVER_HPP

    #include "UDP_Manager.hpp"

    class UDP_Server : public UDP_Manager {
    public:
        UDP_Server();
        ~UDP_Server();

        // Surcharge de l'initialisation spécifique au serveur
        bool initialize(const std::string& configFile, int port = 0) override;

        // Ajouter un client et envoyer une confirmation

    private:
        // Stockage des clients (clé: adresse IP et port, valeur: structure sockaddr_in)
        std::unordered_map<std::string, sockaddr_in> clients;

        // Générer une clé unique pour chaque client (par ex., "IP:PORT")
        std::string generateClientKey(const sockaddr_in& addr) const;
    };

#endif // UDP_SERVER_HPP"