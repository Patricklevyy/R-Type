file(GLOB_RECURSE CLIENT_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
    "{menu}/*.cpp"
)

add_executable(r-type_client ${CLIENT_SRC})
link_common_libraries(r-type_client)
target_link_libraries(r-type_client PRIVATE rtype_shared)