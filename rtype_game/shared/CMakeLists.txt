file(GLOB_RECURSE SHARED_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_library(rtype_shared STATIC ${SHARED_SRC})

target_include_directories(rtype_shared PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(rtype_shared PUBLIC ecs)