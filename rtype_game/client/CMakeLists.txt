add_executable(r-type_client Main.cpp)

target_compile_options(r-type_client PRIVATE -Wall -Wextra -g)

target_link_libraries(r-type_client ecs)

target_include_directories(r-type_client PRIVATE ${CMAKE_SOURCE_DIR}/ecs)

set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})