cmake_minimum_required(VERSION 3.10)
project(RTypeGame)

# Ajouter les sous-dossiers
add_subdirectory(server)
add_subdirectory(client)

# Définir les dépendances communes
set(COMMON_DEPENDENCIES fmt::fmt libconfig::config libconfig::config++)

# Créer une bibliothèque INTERFACE pour partager les dépendances communes
add_library(common_dependencies INTERFACE)

# Ajouter les dépendances communes
target_link_libraries(common_dependencies INTERFACE ${COMMON_DEPENDENCIES})
