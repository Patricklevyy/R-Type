# Récupérer tous les fichiers .cpp du serveur
file(GLOB_RECURSE SERVER_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/components/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/*.cpp"
)

# Créer l'exécutable pour le serveur
add_executable(game_poc_server ${SERVER_SRC})

# Lier les bibliothèques communes
link_common_libraries(game_poc_server)

# Lier également la bibliothèque partagée
target_link_libraries(game_poc_server PRIVATE game_poc_shared)

# Ajouter les répertoires d'inclusion pour le serveur
target_include_directories(game_poc_server PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/components
    ${CMAKE_CURRENT_SOURCE_DIR}/system
)