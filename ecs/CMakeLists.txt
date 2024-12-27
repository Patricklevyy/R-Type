# file(GLOB_RECURSE ECS_SRC
#     "${CMAKE_CURRENT_SOURCE_DIR}/udp/*.cpp"
# )

# add_library(ecs STATIC ${ECS_SRC})

# target_include_directories(ecs PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# find_package(fmt CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)

# target_link_libraries(ecs PUBLIC
#     fmt::fmt
#     libconfig::config
#     libconfig::config++
# )

file(GLOB_RECURSE ECS_SRC
    "${CMAKE_CURRENT_SOURCE_DIR}/udp/*.cpp"
)

add_library(ecs STATIC ${ECS_SRC})

target_include_directories(ecs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}
)

link_common_libraries(ecs)

# add_library(ecs STATIC
#     udp/MessageCompressor.cpp
#     udp/UDP_Client.cpp
#     udp/UDP_Manager.cpp
#     udp/UDP_Server.cpp
# )

# target_include_directories(ecs PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include
#     ${CMAKE_CURRENT_SOURCE_DIR}
# )

# find_package(fmt CONFIG REQUIRED)
# find_package(libconfig CONFIG REQUIRED)

# target_link_libraries(ecs PUBLIC 
#     fmt::fmt
#     libconfig::config
#     libconfig::config++
# )