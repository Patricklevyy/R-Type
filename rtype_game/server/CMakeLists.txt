file(GLOB_RECURSE SOURCE_FILES *.cpp)

add_executable(r-type_server ${SOURCE_FILES})

target_compile_options(r-type_server PRIVATE -Wall -Wextra)

target_link_libraries(r-type_server ECS)

target_include_directories(r-type_server PRIVATE ${CMAKE_SOURCE_DIR}/ECS)

set_target_properties(r-type_server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
