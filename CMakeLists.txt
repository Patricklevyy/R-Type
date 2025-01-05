# cmake_minimum_required(VERSION 3.21)
# project(RType LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# add_compile_options(-Wall -Wextra)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# if(NOT DEFINED ENV{VCPKG_ROOT})
#     message(STATUS "Vcpkg not found in environment. Cloning and setting up vcpkg...")
#     execute_process(COMMAND git clone https://github.com/microsoft/vcpkg.git ${CMAKE_BINARY_DIR}/vcpkg)
#     execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg)
#     set(ENV{VCPKG_ROOT} "${CMAKE_BINARY_DIR}/vcpkg")
# endif()

# set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
# message(STATUS "Using vcpkg from $ENV{VCPKG_ROOT}")

# if(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg.json")
#     set(VCPKG_MANIFEST_MODE ON)
#     message(STATUS "Vcpkg manifest mode activated.")
#     execute_process(
#         COMMAND $ENV{VCPKG_ROOT}/vcpkg install --triplet x64-linux --clean-after-build
#         WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#     )
# endif()

# set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/vcpkg/installed/x64-linux/share" ${CMAKE_PREFIX_PATH})

# find_package(fmt CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)
# find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
# find_package(GTest CONFIG REQUIRED)
# find_package(Catch2 CONFIG REQUIRED)

# set(COMMON_LIBS
#     fmt::fmt
#     libconfig::config
#     libconfig::config++
#     sfml-system
#     sfml-window
#     sfml-graphics
#     sfml-audio
# )

# function(link_common_libraries target)
#     target_link_libraries(${target} PRIVATE ${COMMON_LIBS})
# endfunction()

# add_subdirectory(ecs)
# add_subdirectory(rtype_game/shared)
# add_subdirectory(rtype_game/client)
# add_subdirectory(rtype_game/server)
# add_subdirectory(rtype_game/config)

# include(CTest)
# add_subdirectory(rtype_game/test_unitaire)


cmake_minimum_required(VERSION 3.16)
project(rtype)

# Options générales
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) # Pour les bibliothèques statiques

# Trouver libconfig++
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

# ECS
file(GLOB_RECURSE ECS_SRC_FILES ecs/*.cpp)
add_library(ecs STATIC ${ECS_SRC_FILES})

target_include_directories(ecs PUBLIC
    ${CMAKE_SOURCE_DIR}/ecs
    ${LIBCONFIG_INCLUDE_DIRS}
)
target_link_libraries(ecs PRIVATE ${LIBCONFIG_LIBRARIES})
link_directories(${LIBCONFIG_LIBRARY_DIRS})

# Shared
file(GLOB_RECURSE SHARED_FILES game_poc/shared/*.cpp game_poc/shared/*.h)
add_library(shared STATIC ${SHARED_FILES})

target_include_directories(shared PUBLIC ${CMAKE_SOURCE_DIR}/game_poc/shared)

# Client
file(GLOB_RECURSE CLIENT_FILES game_poc/client/*.cpp game_poc/client/*.h)
add_executable(poc-game_client ${CLIENT_FILES})

target_compile_options(poc-game_client PRIVATE -Wall -Wextra -g)
target_link_libraries(poc-game_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio ecs shared)

# Server
file(GLOB_RECURSE SERVER_FILES game_poc/server/*.cpp game_poc/server/*.h)
add_executable(poc-game_server ${SERVER_FILES})

target_compile_options(poc-game_server PRIVATE -Wall -Wextra -g)
target_link_libraries(poc-game_server PRIVATE sfml-graphics ecs shared)

# Propriétés des exécutables
set_target_properties(poc-game_client poc-game_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)