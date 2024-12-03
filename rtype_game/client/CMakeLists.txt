add_executable(r-type_client Main.cpp)

# Options de compilation
target_compile_options(r-type_client PRIVATE -Wall -Wextra)

# Forcer le chemin de l'exécutable à la racine
set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
