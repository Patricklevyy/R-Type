file(GLOB_RECURSE SERVER_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(r-type_server ${SERVER_SRC})
link_common_libraries(r-type_server)
target_link_libraries(r-type_server PRIVATE rtype_shared)