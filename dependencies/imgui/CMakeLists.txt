cmake_minimum_required(VERSION 3.12)
project(ImGui VERSION 0.0.0)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_library(imgui STATIC ${SRCS} ${HDRS})

set_target_properties(imgui PROPERTIES UNITY_BUILD ON)
set_target_properties(imgui PROPERTIES UNITY_BUILD_BATCH_SIZE 15)

target_include_directories(
    imgui
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../GLEW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../SDL2/include/SDL2
)