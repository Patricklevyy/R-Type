# # file(GLOB_RECURSE SERVER_SRC
# #     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
# # )

# # add_executable(r-type_server ${SERVER_SRC})

# # find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
# # find_package(libconfig CONFIG REQUIRED)

# # target_link_libraries(r-type_server PRIVATE
# #     rtype_shared
# #     sfml-system
# #     sfml-window
# #     sfml-graphics
# #     sfml-audio
# #     libconfig::config
# #     libconfig::config++
# # )

# file(GLOB_RECURSE SERVER_SRC
#     "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
# )

# add_executable(r-type_server ${SERVER_SRC})
# link_common_libraries(r-type_server)
# target_link_libraries(r-type_server PRIVATE rtype_shared)

# # add_executable(r-type_server
# #     Room.cpp
# #     Room_Create_And_Kill.cpp
# #     Room_Event_Bus.cpp
# #     Room_Game_Loop.cpp
# #     Room_Send_Message.cpp
# #     Server.cpp
# #     Server_Create_And_Join_Room.cpp
# #     Main.cpp
# # )

# # find_package(SFML COMPONENTS system window graphics audio CONFIG REQUIRED)
# # find_package(libconfig CONFIG REQUIRED)

# # target_link_libraries(r-type_server PRIVATE
# #     rtype_shared
# #     sfml-system
# #     sfml-window
# #     sfml-graphics
# #     sfml-audio
# #     libconfig::config
# #     libconfig::config++
# # )