cmake_minimum_required(VERSION 3.16)
project(rtype LANGUAGES CXX)

# Utiliser vcpkg comme gestionnaire de paquets
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# Activer C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler selon l'OS
if (WIN32)
    add_compile_definitions(_WIN32_WINNT=0x0A00)
    add_compile_options(/W3) # MSVC
else()
    add_compile_options(-Wall -Wextra)
endif()

# Rechercher les dépendances
find_package(fmt CONFIG REQUIRED)
find_package(libconfig CONFIG REQUIRED)
find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics audio network)

# Rechercher récursivement les fichiers sources pour ECS
file(GLOB_RECURSE ECS_SRC_FILES "${CMAKE_SOURCE_DIR}/ecs/*.cpp")

# Ajouter ECS comme bibliothèque statique
add_library(ecs STATIC ${ECS_SRC_FILES})
target_include_directories(ecs PUBLIC "${CMAKE_SOURCE_DIR}/ecs")
target_link_libraries(ecs PRIVATE libconfig::config++)

# Rechercher récursivement les fichiers partagés entre client et serveur
file(GLOB_RECURSE SHARED_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp" "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.h")

# Ajouter les fichiers partagés comme bibliothèque statique
add_library(shared STATIC ${SHARED_SRC_FILES})
target_include_directories(shared PUBLIC "${CMAKE_SOURCE_DIR}/rtype_game/shared")

# Ajouter les sources du client
file(GLOB_RECURSE CLIENT_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/client/*.cpp")
add_executable(r-type_client ${CLIENT_SRC_FILES})
target_link_libraries(r-type_client PRIVATE ecs shared fmt::fmt sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_include_directories(r-type_client PRIVATE "${CMAKE_SOURCE_DIR}/ecs")

# Ajouter les sources du serveur
file(GLOB_RECURSE SERVER_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/server/*.cpp")
add_executable(r-type_server ${SERVER_SRC_FILES})
target_link_libraries(r-type_server PRIVATE ecs shared fmt::fmt)
target_include_directories(r-type_server PRIVATE "${CMAKE_SOURCE_DIR}/ecs")

# Définir les répertoires de sortie des exécutables
set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")



###############Bas=GOOOOOOOD############################################################################################

# cmake_minimum_required(VERSION 3.16)
# project(rtype LANGUAGES CXX)

# # Utiliser vcpkg comme gestionnaire de paquets
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# # Vérifie et installe automatiquement les dépendances via vcpkg
# execute_process(
#     COMMAND ${CMAKE_COMMAND} -E env ${CMAKE_SOURCE_DIR}/vcpkg/vcpkg install
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#     RESULT_VARIABLE VCPKG_RESULT
#     OUTPUT_VARIABLE VCPKG_OUTPUT
#     ERROR_VARIABLE VCPKG_ERROR
# )

# # Affiche les messages de vcpkg dans le terminal
# if(VCPKG_RESULT)
#     message(FATAL_ERROR "vcpkg install failed:\n${VCPKG_ERROR}")
# else()
#     message(STATUS "vcpkg install successful:\n${VCPKG_OUTPUT}")
# endif()

# # Activer C++17
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# # Activer les warnings
# add_compile_options(-Wall -Wextra)
# # add_compile_options(-Wall -Wextra -Werror) #A rajouter quand il n'y aura plus de problème dans l'ecs

# # Rechercher automatiquement les dépendances définies dans vcpkg.json
# find_package(fmt CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)
# find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics audio network)

# # Rechercher récursivement les fichiers sources pour ECS
# file(GLOB_RECURSE ECS_SRC_FILES "${CMAKE_SOURCE_DIR}/ecs/*.cpp")

# # Ajouter ECS comme bibliothèque statique
# add_library(ecs STATIC ${ECS_SRC_FILES})
# target_include_directories(ecs PUBLIC "${CMAKE_SOURCE_DIR}/ecs")
# target_link_libraries(ecs PRIVATE libconfig::config++)

# # Rechercher récursivement les fichiers partagés entre client et serveur
# file(GLOB_RECURSE SHARED_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.cpp" "${CMAKE_SOURCE_DIR}/rtype_game/shared/*.h")

# # Ajouter les fichiers partagés comme bibliothèque statique
# add_library(shared STATIC ${SHARED_SRC_FILES})
# target_include_directories(shared PUBLIC "${CMAKE_SOURCE_DIR}/rtype_game/shared")

# # Ajouter les sources du client
# file(GLOB_RECURSE CLIENT_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/client/*.cpp")
# add_executable(r-type_client ${CLIENT_SRC_FILES})
# target_link_libraries(r-type_client PRIVATE ecs shared fmt::fmt sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
# target_include_directories(r-type_client PRIVATE "${CMAKE_SOURCE_DIR}/ecs")

# # Ajouter les sources du serveur
# file(GLOB_RECURSE SERVER_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/server/*.cpp")
# add_executable(r-type_server ${SERVER_SRC_FILES})
# target_link_libraries(r-type_server PRIVATE ecs shared fmt::fmt)
# target_include_directories(r-type_server PRIVATE "${CMAKE_SOURCE_DIR}/ecs")

# # Définir les répertoires de sortie des exécutables
# set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
# set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

##########################HAUT = GOOOOOOODDDDDDDDDDDD###################################################


# cmake_minimum_required(VERSION 3.16)
# project(rtype LANGUAGES CXX)

# # Utiliser vcpkg comme gestionnaire de paquets
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# # Vérifie et installe automatiquement les dépendances via vcpkg
# execute_process(
#     COMMAND ${CMAKE_COMMAND} -E env ${CMAKE_SOURCE_DIR}/vcpkg/vcpkg install
#     WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
#     RESULT_VARIABLE VCPKG_RESULT
#     OUTPUT_VARIABLE VCPKG_OUTPUT
#     ERROR_VARIABLE VCPKG_ERROR
# )

# # Affiche les messages de vcpkg dans le terminal
# if(VCPKG_RESULT)
#     message(FATAL_ERROR "vcpkg install failed:\n${VCPKG_ERROR}")
# else()
#     message(STATUS "vcpkg install successful:\n${VCPKG_OUTPUT}")
# endif()

# # Activer C++17
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

# # Activer les warnings
# # add_compile_options(-Wall -Wextra -Werror)

# # Rechercher automatiquement les dépendances définies dans vcpkg.json
# find_package(fmt CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)

# # Rechercher récursivement les fichiers sources pour ECS
# file(GLOB_RECURSE ECS_SRC_FILES "${CMAKE_SOURCE_DIR}/ecs/*.cpp")

# # Ajouter ECS comme bibliothèque statique
# add_library(ecs STATIC ${ECS_SRC_FILES})
# target_include_directories(ecs PUBLIC "${CMAKE_SOURCE_DIR}/ecs")
# target_link_libraries(ecs PRIVATE libconfig::config++)

# # Ajouter les sources du client
# file(GLOB_RECURSE CLIENT_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/client/*.cpp")
# add_executable(r-type_client ${CLIENT_SRC_FILES})
# target_link_libraries(r-type_client PRIVATE ecs fmt::fmt)
# target_include_directories(r-type_client PRIVATE "${CMAKE_SOURCE_DIR}/ecs")

# # Ajouter les sources du serveur
# file(GLOB_RECURSE SERVER_SRC_FILES "${CMAKE_SOURCE_DIR}/rtype_game/server/*.cpp")
# add_executable(r-type_server ${SERVER_SRC_FILES})
# target_link_libraries(r-type_server PRIVATE ecs fmt::fmt)
# target_include_directories(r-type_server PRIVATE "${CMAKE_SOURCE_DIR}/ecs")

# # Définir les répertoires de sortie des exécutables
# set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
# set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

########################################################################""

# cmake_minimum_required(VERSION 3.16)
# project(rtype)

# # Utiliser vcpkg comme gestionnaire de package
# set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

# # Activer les warnings et le support de C++17
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)
# add_compile_options(-Wall -Wextra -Werror)

# # Ajouter les sous-dossiers
# add_subdirectory(ecs)
# add_subdirectory(rtype_game/client)
# add_subdirectory(rtype_game/server)
