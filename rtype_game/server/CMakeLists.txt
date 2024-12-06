# # Déclare le serveur
# project(r-type_server)

# # Trouver tous les fichiers source dans le répertoire server
# file(GLOB_RECURSE SERVER_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# # Ajouter l'exécutable
# add_executable(r-type_server ${SERVER_SRC_FILES})

# # Ajouter les options de compilation
# target_compile_options(r-type_server PRIVATE -Wall -Wextra -g)

# # Lier ECS et les dépendances
# target_link_libraries(r-type_server PRIVATE ecs)

# # Ajouter les includes nécessaires
# target_include_directories(r-type_server PRIVATE ${CMAKE_SOURCE_DIR}/ecs)

# # Spécifier le répertoire de sortie
# set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
