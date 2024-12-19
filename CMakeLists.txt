cmake_minimum_required(VERSION 3.16)
project(rtype)

# Options générales
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Pour les bibliothèques statiques

# Rechercher OpenSSL
find_package(OpenSSL REQUIRED)

# Trouver libconfig++
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

# ECS
file(GLOB_RECURSE ECS_SRC_FILES ecs/*.cpp)
add_library(ecs STATIC ${ECS_SRC_FILES})

target_include_directories(ecs PUBLIC
    ${CMAKE_SOURCE_DIR}/ecs
    ${LIBCONFIG_INCLUDE_DIRS}
    ${OPENSSL_INCLUDE_DIR}
)
target_link_libraries(ecs PRIVATE ${LIBCONFIG_LIBRARIES} OpenSSL::Crypto OpenSSL::SSL)
link_directories(${LIBCONFIG_LIBRARY_DIRS})

# Shared
file(GLOB_RECURSE SHARED_FILES rtype_game/shared/*.cpp rtype_game/shared/*.h)
add_library(shared STATIC ${SHARED_FILES})

target_include_directories(shared PUBLIC ${CMAKE_SOURCE_DIR}/rtype_game/shared)

# Client
file(GLOB_RECURSE CLIENT_FILES rtype_game/client/*.cpp rtype_game/client/*.h)
add_executable(r-type_client ${CLIENT_FILES})

target_compile_options(r-type_client PRIVATE -Wall -Wextra -g)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics ecs shared)

# Server
file(GLOB_RECURSE SERVER_FILES rtype_game/server/*.cpp rtype_game/server/*.h)
add_executable(r-type_server ${SERVER_FILES})

target_compile_options(r-type_server PRIVATE -Wall -Wextra -g)
target_link_libraries(r-type_server PRIVATE ecs shared)

# Propriétés des exécutables
set_target_properties(r-type_client r-type_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)