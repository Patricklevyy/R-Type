# # Déclare le client
# project(r-type_client)

# # Ajouter l'exécutable
# add_executable(r-type_client Main.cpp)

# # Ajouter les options de compilation
# target_compile_options(r-type_client PRIVATE -Wall -Wextra -g)

# # Lier ECS et les dépendances
# target_link_libraries(r-type_client PRIVATE ecs)

# # Ajouter les includes nécessaires
# target_include_directories(r-type_client PRIVATE ${CMAKE_SOURCE_DIR}/ecs)

# # Spécifier le répertoire de sortie
# set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
