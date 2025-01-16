# Récupérer tous les fichiers .cpp du client
file(GLOB_RECURSE CLIENT_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/components/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/*.cpp"
)

# Créer l'exécutable pour le client
add_executable(game_poc_client ${CLIENT_SRC})

# Lier les bibliothèques communes
link_common_libraries(game_poc_client)

# Lier également la bibliothèque partagée
target_link_libraries(game_poc_client PRIVATE game_poc_shared)

# Ajouter les répertoires d'inclusion pour le client
target_include_directories(game_poc_client PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/components
    ${CMAKE_CURRENT_SOURCE_DIR}/system
)
