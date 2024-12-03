cmake_minimum_required(VERSION 3.16)
project(rtype)

# Inclure le sous-dossier rtype_game
message(STATUS "Adding subdirectory: ${CMAKE_SOURCE_DIR}/rtype_game")
add_subdirectory(rtype_game)
message(STATUS "it is add")
