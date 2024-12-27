# file(GLOB_RECURSE CLIENT_SRC
#     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
# )

# add_executable(r-type_client ${CLIENT_SRC})

# find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)

# target_link_libraries(r-type_client PRIVATE
#     rtype_shared
#     sfml-system
#     sfml-window
#     sfml-graphics
#     sfml-audio
#     libconfig::config
#     libconfig::config++
# )

file(GLOB_RECURSE CLIENT_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(r-type_client ${CLIENT_SRC})
link_common_libraries(r-type_client)
target_link_libraries(r-type_client PRIVATE rtype_shared)

# add_executable(r-type_client
#     Client.cpp
#     Client_Create_And_Kill.cpp
#     Client_Event_Bus.cpp
#     Client_Event_Sfml.cpp
#     Client_Init.cpp
#     Client_Send_Message.cpp
#     Command_checker.cpp
#     Main.cpp
# )

# find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)

# target_link_libraries(r-type_client PRIVATE
#     rtype_shared
#     sfml-system
#     sfml-window
#     sfml-graphics
#     sfml-audio
#     libconfig::config
#     libconfig::config++
# )