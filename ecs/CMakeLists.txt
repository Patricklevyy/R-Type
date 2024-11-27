# Déclare le projet ecs
project(ecs)

# Rechercher récursivement tous les fichiers .cpp dans le répertoire ecs
file(GLOB_RECURSE ECS_SRC_FILES "${CMAKE_SOURCE_DIR}/ecs/*.cpp")

# Créer la bibliothèque ECS
add_library(ecs STATIC ${ECS_SRC_FILES})

# Inclure le répertoire ecs pour permettre d'accéder aux fichiers d'en-tête
target_include_directories(ecs PUBLIC "${PROJECT_SOURCE_DIR}/ecs")

# Trouver et lier la bibliothèque libconfig++
find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

# Inclure et lier les dépendances de libconfig++
target_include_directories(ecs PUBLIC ${LIBCONFIG_INCLUDE_DIRS})
target_link_libraries(ecs ${LIBCONFIG_LIBRARIES})
link_directories(${LIBCONFIG_LIBRARY_DIRS})
