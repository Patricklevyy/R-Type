# Récupérer tous les fichiers .cpp de la partie partagée
file(GLOB_RECURSE SHARED_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/system/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/components/*.cpp"
)

# Créer une bibliothèque statique pour le code partagé
add_library(game_poc_shared STATIC ${SHARED_SRC})

# Ajouter les répertoires d'inclusion publics pour le code partagé
target_include_directories(game_poc_shared PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/system
    ${CMAKE_CURRENT_SOURCE_DIR}/components
)

# Lier la bibliothèque ECS si nécessaire
target_link_libraries(game_poc_shared PUBLIC ecs)