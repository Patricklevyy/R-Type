add_executable(r-type_client Main.cpp)

target_compile_options(r-type_client PRIVATE -Wall -Wextra)

target_link_libraries(r-type_client ECS)

target_include_directories(r-type_client PRIVATE ${CMAKE_SOURCE_DIR}/ECS)

set_target_properties(r-type_client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
