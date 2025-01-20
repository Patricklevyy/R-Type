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

    /**
     * @brief Test behavior when no configuration file is found.
     */
    void test_no_config_file()
    {
        ecs::udp::UDP_Manager udp_manager;

        udp_manager.initialize("no_config_file.conf");
    }

    /**
     * @brief Test behavior when the configuration file is missing the secret key.
     */
    void test_no_secret_key()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_with_no_secret_key.config");
    }

    /**
     * @brief Test behavior when the buffer size in the configuration file is invalid.
     */
    void test_wrong_buffer_size()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_with_wrong_buffer_size.config");
    }

    /**
     * @brief Test behavior when the port specified in the configuration file is already in use.
     */
    void test_port_already_used()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_file.config");
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_file.config");
    }


    /**
     * @brief Test behavior when the configuration file is missing the IP address.
     */
    void test_no_ip()
    {
        ecs::udp::UDP_Manager udp_manager;
        udp_manager.initialize("rtype_game/test_unitaire/files_tests/config_with_no_ip.config");
    }

    /**
     * @brief Test behavior when attempting to send a message without initializing the UDP manager.
     */
    void test_send_message_with_no_init()
    {
        ecs::udp::UDP_Manager udp_manager;

        udp_manager.sendMessage(std::vector<char>(), "");
    }

    /**
     * @brief Test behavior when attempting to send a message that exceeds the buffer size limit.
     */
    void test_send_message_to_big()
    {
        ecs::udp::UDP_Manager udp_manager;

        constexpr size_t TOO_BIG_SIZE = 1500;
        std::vector<char> big_message(TOO_BIG_SIZE, 'A');
        std::string empty_target = "";

        udp_manager.sendMessage(big_message, "127.0.0.1:8080");
    }


#endif /* !CONNEXION_TESTS_HPP_ */
