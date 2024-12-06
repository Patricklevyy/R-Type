# # Déclare le projet ECS
# project(ecs)

# # Trouver tous les fichiers source dans le répertoire ecs
# file(GLOB_RECURSE ECS_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# # Créer une bibliothèque ECS
# add_library(ecs STATIC ${ECS_SRC_FILES})

# # Ajouter les includes
# target_include_directories(ecs PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# # Lier libconfig via vcpkg
# find_package(libconfig CONFIG REQUIRED)
# target_link_libraries(ecs PRIVATE libconfig::config++)
