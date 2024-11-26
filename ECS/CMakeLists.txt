project(ECS)

file(GLOB ECS_SRC_FILES "${CMAKE_SOURCE_DIR}/ECS/*.cpp")

add_library(ECS STATIC ${ECS_SRC_FILES})

target_include_directories(ECS PUBLIC "${PROJECT_SOURCE_DIR}/ECS")

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCONFIG REQUIRED libconfig++)

target_include_directories(ECS PUBLIC ${LIBCONFIG_INCLUDE_DIRS})

target_link_libraries(ECS ${LIBCONFIG_LIBRARIES})

link_directories(${LIBCONFIG_LIBRARY_DIRS})
