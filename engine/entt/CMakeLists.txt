cmake_minimum_required(VERSION 3.16)
project(entt VERSION 0.0.0)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_library(entt SHARED ${SRCS} ${HDRS})

set_target_properties(
    entt PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

add_definitions(-D"GLM_FORCE_SWIZZLE")
add_definitions(-D"ENTT_API_EXPORT")

target_link_libraries(entt Engine)

target_include_directories(
    entt PUBLIC
    ${CMAKE_SOURCE_DIR}/engine/include
    ${CMAKE_SOURCE_DIR}/dependencies/entt/include
)