cmake_minimum_required(VERSION 3.21)
project(RType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Vérification et configuration de Vcpkg
if(DEFINED ENV{VCPKG_ROOT})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")
    message(STATUS "Using vcpkg from $ENV{VCPKG_ROOT}")
else()
    message(FATAL_ERROR "Vcpkg is not found. Please define VCPKG_ROOT or install Vcpkg.")
endif()

# Activation du manifeste Vcpkg
if(EXISTS "${CMAKE_SOURCE_DIR}/vcpkg.json")
    set(VCPKG_MANIFEST_MODE ON)
    message(STATUS "Vcpkg manifest mode activated.")
else()
    message(WARNING "vcpkg.json not found. Ensure dependencies are managed correctly.")
endif()

# Commande pour installer automatiquement les dépendances avec vcpkg
if(VCPKG_MANIFEST_MODE)
    message(STATUS "Ensuring dependencies are installed via vcpkg...")
    execute_process(
        COMMAND vcpkg install --triplet x64-linux --clean-after-build
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
target_link_libraries(r-type_server PRIVATE ecs shared sfml-graphics sfml-window sfml-system)

# Propriétés des exécutables
set_target_properties(r-type_client r-type_server PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)