cmake_minimum_required(VERSION 3.16)
project(BubbleEditorUI VERSION 0.0.0)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_library(BubbleEditorUI SHARED ${SRCS} ${HDRS})

set_target_properties(
    BubbleEditorUI PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

add_definitions(-D"GLM_FORCE_SWIZZLE")

target_link_libraries(BubbleEditorUI Engine)
target_link_libraries(BubbleEditorUI imgui)
target_link_libraries(BubbleEditorUI nativefiledialog)

target_include_directories(
    BubbleEditorUI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../editor_common
    ${CMAKE_SOURCE_DIR}/engine/include
    ${CMAKE_SOURCE_DIR}/dependencies/DHR/include
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/include
)

# PCH
target_precompile_headers(
    BubbleEditorUI PRIVATE
    ${CMAKE_SOURCE_DIR}/engine/include/engine.h
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/include/imgui.h
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/include/imgui_impl_opengl3.h
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/include/imgui_impl_sdl.h
)

