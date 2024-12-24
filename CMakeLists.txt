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
else()
    message(WARNING "vcpkg.json not found. Ensure dependencies are managed correctly.")
endif()

if(VCPKG_MANIFEST_MODE)
    message(STATUS "Ensuring dependencies are installed via vcpkg...")
    execute_process(
        COMMAND $ENV{VCPKG_ROOT}/vcpkg install --triplet x64-linux --clean-after-build
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/vcpkg/installed/x64-linux/share" ${CMAKE_PREFIX_PATH})

find_package(fmt CONFIG REQUIRED)
find_package(libconfig CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

function(resolve_dependency target lib)
    if(${lib}_FOUND)
        message(STATUS "${lib} found locally.")
    else()
        message(STATUS "${lib} not found, will use vcpkg-installed version.")
    endif()
    target_link_libraries(${target} PRIVATE ${lib})
endfunction()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ecs/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype_game/include)

file(GLOB_RECURSE CLIENT_SRC
    "${CMAKE_SOURCE_DIR}/rtype_game/client/*.cpp"
    "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp"
    "${CMAKE_SOURCE_DIR}/ecs/*.cpp"
)

file(GLOB_RECURSE SERVER_SRC
    "${CMAKE_SOURCE_DIR}/rtype_game/server/*.cpp"
    "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp"
    "${CMAKE_SOURCE_DIR}/ecs/*.cpp"
)

add_executable(r-type_client ${CLIENT_SRC})
add_executable(r-type_server ${SERVER_SRC})

resolve_dependency(r-type_client fmt::fmt)
resolve_dependency(r-type_server fmt::fmt)
resolve_dependency(r-type_client libconfig::config++)
resolve_dependency(r-type_server libconfig::config++)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)
target_link_libraries(r-type_server PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)

install(TARGETS r-type_client r-type_server RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})

# Activer CTest
include(CTest)

# Trouver les dépendances nécessaires
find_package(GTest CONFIG REQUIRED)
find_package(Catch2 CONFIG REQUIRED)

# Définir les fichiers sources pour les tests
file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_SOURCE_DIR}/rtype_game/test_unitaire/*.cpp"
    "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp"
    "${CMAKE_SOURCE_DIR}/ecs/*.cpp"
)

# Ajouter un exécutable pour les tests
add_executable(r-type_tests ${TEST_SOURCES})

# Lier les bibliothèques nécessaires
target_link_libraries(r-type_tests PRIVATE
    fmt::fmt
    libconfig::config++
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
    GTest::gtest
    GTest::gtest_main
)

# Activer les tests dans CTest
add_test(NAME RTypeTests COMMAND r-type_tests)

# Ajouter une commande personnalisée pour exécuter les tests
add_custom_target(run_tests
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    DEPENDS r-type_tests
)