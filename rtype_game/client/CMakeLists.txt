cmake_minimum_required(VERSION 3.10)
project(RTypeClient)

# Liste des fichiers sources
set(SOURCES Main.cpp)

# Création de l'exécutable
add_executable(r-type_client ${SOURCES})

# Lier les dépendances communes
target_link_libraries(r-type_client PRIVATE common_dependencies)
