cmake_minimum_required(VERSION 3.12)
project(BubbleEditor VERSION 0.0.0)

 
file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_executable(BubbleEditor ${SRCS} ${HDRS})

# Libraries
target_link_libraries(BubbleEditor Engine)
target_link_libraries(BubbleEditor imgui)
target_link_libraries(BubbleEditor nativefiledialog)


set_target_properties(
    BubbleEditor PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Defines
add_definitions(-D"GLM_FORCE_SWIZZLE")


# Include directories
target_include_directories(
    BubbleEditor PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ui
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/imgui/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/nativefiledialog/src/include
)

# Temp resources
add_custom_command(TARGET BubbleEditor PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/resources
                       $<TARGET_FILE_DIR:BubbleEditor>/resources)

# Put dll files to exe
add_custom_command(TARGET BubbleEditor PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/../dependencies/dll
                       $<TARGET_FILE_DIR:BubbleEditor>)
