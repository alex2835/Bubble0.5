cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 0.0.0)

 
file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_executable(Bubble ${SRCS} ${HDRS})


# Libraries
target_link_libraries(Bubble Engine)
target_link_libraries(Bubble imgui)
target_link_libraries(Bubble nativefiledialog)


set_target_properties(
    Bubble PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Defines
add_definitions(-D"GLM_SWIZZLE")


# Include directories
target_include_directories(
    Bubble PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/imgui/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/nativefiledialog/src/include
)

# Temp resources
add_custom_command(TARGET Bubble PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/resources
                       $<TARGET_FILE_DIR:Bubble>/resources)

# Put dll files to exe
add_custom_command(TARGET Bubble PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/../dependencies/dll
                       $<TARGET_FILE_DIR:Bubble>)
