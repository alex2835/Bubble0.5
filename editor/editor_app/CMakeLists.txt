cmake_minimum_required(VERSION 3.18)
project(BubbleEditorApp VERSION 0.0.0)
 
file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_executable(BubbleEditorApp ${SRCS} ${HDRS})

target_link_libraries(BubbleEditorApp imgui)
target_link_libraries(BubbleEditorApp Engine)
target_link_libraries(BubbleEditorApp nativefiledialog)
target_link_libraries(BubbleEditorApp BubbleEditorUI)

set_target_properties(
    BubbleEditorApp PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Defines
add_definitions(-D"GLM_FORCE_SWIZZLE")
add_definitions(-D"_NO_DEBUG_HEAP=1")

# Include directories
target_include_directories(
    BubbleEditorApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../editor_common
    ${CMAKE_SOURCE_DIR}/engine/include
    ${CMAKE_SOURCE_DIR}/dependencies/imgui/include
    ${CMAKE_SOURCE_DIR}/dependencies/nativefiledialog/src/include
    ${CMAKE_SOURCE_DIR}/dependencies/DHR/include
)

# PCH
target_precompile_headers(BubbleEditorApp REUSE_FROM Engine)

# Temp resources
add_custom_command(TARGET BubbleEditorApp PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/resources
                       $<TARGET_FILE_DIR:BubbleEditorApp>/resources)

# Put dll files to exe
add_custom_command(TARGET BubbleEditorApp PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/dependencies/dll
                       $<TARGET_FILE_DIR:BubbleEditorApp>)