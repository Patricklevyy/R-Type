/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** connection_tests
*/

#include <gtest/gtest.h>

#include "connexion_tests.hpp"
#include "ecs_tests.hpp"
#include "../../ecs/EcsExceptions.hpp"

// TESTS ON THE CONNECTION AND INITIALISATION BETWEEN SERVER AND CLIENT

TEST(ConnexionTest, NoConfigFile) {
    EXPECT_THROW(test_no_config_file(), ecs::ERROR::CantReadConfigFileExceptions);
}

TEST(ConnexionTest, NoSecretKey) {
    EXPECT_THROW(test_no_secret_key(), ecs::ERROR::MissingSecretKeyInConfigFileException);
}

TEST(ConnexionTest, WrongBufferSize) {
    EXPECT_THROW(test_wrong_buffer_size(), ecs::ERROR::WrongBufferSizeExceptions);
}

TEST(ConnexionTest, PortAlreadyUsed) {
    EXPECT_THROW(test_port_already_used(), ecs::ERROR::BindFailedExceptions);
}

TEST(ConnexionTest, TestNoIp) {
    EXPECT_THROW(test_no_ip(), ecs::ERROR::WrongConfigurationExceptions);
}

// TESTS ON SENDING MESSAGES

TEST(SendMessageTest, SendWithoutInit) {
    EXPECT_THROW(test_send_message_with_no_init(), ecs::ERROR::InvalidAdressFormatExceptions);
}

TEST(SendMessageTest, SendMessageToBig) {
    EXPECT_THROW(test_send_message_to_big(), ecs::ERROR::MessageTooBigExceptions);
}

// TESTS ON ECS

TEST(EcsTests, RegistryAlreadyExist) {
    EXPECT_THROW(add_registry_already_exist(), ecs::ERROR::ComponentTypeAlreadyExistException);
}

TEST(EcsTests, ComponentDontExist) {
    EXPECT_THROW(add_component_dont_exist(), ecs::ERROR::ComponentNotFoundExceptions);
}
