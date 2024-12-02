cmake_minimum_required(VERSION 3.21)
project(RType LANGUAGES CXX)

# Définir le standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Activer les warnings
add_compile_options(-Wall -Wextra)

# Gestion dynamique de vcpkg
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
    message(STATUS "Utilisation de vcpkg détectée : $ENV{VCPKG_ROOT}")
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()

# Charger les dépendances définies dans vcpkg.json
find_package(fmt CONFIG REQUIRED)
find_package(libconfig CONFIG REQUIRED)

# Répertoires globaux de sortie
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ajouter les sous-dossiers
add_subdirectory(rtype_game)



# cmake_minimum_required(VERSION 3.14)
# project(RType LANGUAGES CXX)

# # Version du standard C++
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Activer les warnings
# add_compile_options(-Wall -Wextra)

# # Gestion dynamique de vcpkg
# if(NOT DEFINED CMAKE_TOOLCHAIN_FILE AND DEFINED ENV{VCPKG_ROOT})
#     message(STATUS "Utilisation de vcpkg détectée : $ENV{VCPKG_ROOT}")
#     set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
# endif()

# # Vérification des dépendances
# find_package(fmt CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)

# # Définir les répertoires de sortie globaux
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# # Déclarer les sous-projets
# add_subdirectory(rtype_game)
