file(GLOB_RECURSE ECS_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/udp/*.cpp"
)

add_library(ecs STATIC ${ECS_SRC})

target_include_directories(ecs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

link_common_libraries(ecs)