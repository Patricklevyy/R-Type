add_executable(r-type_server Main.cpp)

# Options de compilation
target_compile_options(r-type_server PRIVATE -Wall -Wextra)

# Forcer le chemin de l'exécutable à la racine
set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
