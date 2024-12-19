cmake_minimum_required(VERSION 3.21)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

# Vérification et configuration automatique de Vcpkg
if(NOT DEFINED ENV{VCPKG_ROOT})
    message(STATUS "Vcpkg not found in environment. Cloning and setting up vcpkg...")
    execute_process(COMMAND git clone https://github.com/microsoft/vcpkg.git ${CMAKE_BINARY_DIR}/vcpkg)
    execute_process(COMMAND ${CMAKE_BINARY_DIR}/vcpkg/bootstrap-vcpkg.sh WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/vcpkg)
    set(ENV{VCPKG_ROOT} "${CMAKE_BINARY_DIR}/vcpkg")
endif()

# Définir le chemin du toolchain file de Vcpkg
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
message(STATUS "Using vcpkg from $ENV{VCPKG_ROOT}")

# Activer le manifeste Vcpkg si présent
if(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg.json")
    set(VCPKG_MANIFEST_MODE ON)
    message(STATUS "Vcpkg manifest mode activated.")
else()
    message(WARNING "vcpkg.json not found. Ensure dependencies are managed correctly.")
endif()

# Installation des dépendances avec Vcpkg
if(VCPKG_MANIFEST_MODE)
    message(STATUS "Ensuring dependencies are installed via vcpkg...")
    execute_process(
        COMMAND $ENV{VCPKG_ROOT}/vcpkg install --triplet x64-linux --clean-after-build
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

# Recherche des packages
find_package(fmt CONFIG REQUIRED)
find_package(libconfig CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)

# Fonction pour gérer les dépendances
function(resolve_dependency target lib)
    if(${lib}_FOUND)
        message(STATUS "${lib} found locally.")
    else()
        message(STATUS "${lib} not found, will use vcpkg-installed version.")
    endif()
    target_link_libraries(${target} PRIVATE ${lib})
endfunction()

# Ajout des répertoires d'inclusion
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/ecs/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/rtype_game/include)

# Gestion des fichiers source
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

# Création des exécutables
add_executable(r-type_client ${CLIENT_SRC})
add_executable(r-type_server ${SERVER_SRC})

# Liens avec les bibliothèques
resolve_dependency(r-type_client fmt::fmt)
resolve_dependency(r-type_server fmt::fmt)
resolve_dependency(r-type_client libconfig::config++)
resolve_dependency(r-type_server libconfig::config++)
target_link_libraries(r-type_client PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)
target_link_libraries(r-type_server PRIVATE sfml-system sfml-window sfml-graphics sfml-audio libconfig::config libconfig::config++)

# Installation
install(TARGETS r-type_client r-type_server RUNTIME DESTINATION ${CMAKE_SOURCE_DIR})