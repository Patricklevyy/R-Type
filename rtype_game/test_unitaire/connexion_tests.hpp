/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** connexion_tests
*/

#ifndef CONNEXION_TESTS_HPP_
    #define CONNEXION_TESTS_HPP_

    #include "../../ecs/udp/UDP_Client.hpp"
    #include "../../ecs/udp/UDP_Server.hpp"

    void test_no_config_file()
    {
        ecs::udp::UDP_Manager udp_manager;

        udp_manager.initialize("no_config_file.conf");
    }

    void test_no_secret_key()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_with_no_secret_key.config");
    }

    void test_wrong_buffer_size()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_with_wrong_buffer_size.config");
    }

    void test_port_already_used()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_file.config");
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_file.config");
    }

    void test_no_ip()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_with_no_ip.config");
    }

    void test_send_message_with_no_init()
    {
        ecs::udp::UDP_Manager udp_manager;

        udp_manager.sendMessage(std::vector<char>(), "");
    }

    void test_send_message_to_big()
    {
        ecs::udp::UDP_Manager udp_manager;

        constexpr size_t TOO_BIG_SIZE = 1500;
        std::vector<char> big_message(TOO_BIG_SIZE, 'A');
        std::string empty_target = "";

        udp_manager.sendMessage(big_message, "127.0.0.1:8080");
    }


#endif /* !CONNEXION_TESTS_HPP_ */
