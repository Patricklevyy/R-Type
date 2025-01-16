cmake_minimum_required(VERSION 3.21)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

if(NOT DEFINED ENV{VCPKG_ROOT})
    message(STATUS "Vcpkg not found in environment. Cloning and setting up vcpkg...")
    execute_process(COMMAND git clone https://github.com/microsoft/vcpkg.git ${CMAKE_BINARY_DIR}/vcpkg)
    execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg)
    set(ENV{VCPKG_ROOT} "${CMAKE_BINARY_DIR}/vcpkg")
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
message(STATUS "Using vcpkg from $ENV{VCPKG_ROOT}")

if(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg.json")
    set(VCPKG_MANIFEST_MODE ON)
    message(STATUS "Vcpkg manifest mode activated.")
    execute_process(
        COMMAND $ENV{VCPKG_ROOT}/vcpkg install --triplet x64-linux --clean-after-build
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/vcpkg/installed/x64-linux/share" ${CMAKE_PREFIX_PATH})

find_package(fmt CONFIG REQUIRED)
find_package(libconfig CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)

set(COMMON_LIBS
    fmt::fmt
    config
    config++
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

function(link_common_libraries target)
    target_link_libraries(${target} PRIVATE ${COMMON_LIBS})
endfunction()

add_subdirectory(ecs)
add_subdirectory(rtype_game/shared)
add_subdirectory(rtype_game/client)
add_subdirectory(rtype_game/server)
add_subdirectory(rtype_game/config)
add_subdirectory(game_poc/shared)
add_subdirectory(game_poc/client)
add_subdirectory(game_poc/server)
add_subdirectory(game_poc/config)

include(CTest)
add_subdirectory(rtype_game/test_unitaire)
