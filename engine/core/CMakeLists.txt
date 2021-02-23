cmake_minimum_required(VERSION 3.16)

project(Engine VERSION 0.0.0)

file(GLOB_RECURSE SRCS *.cpp)
file(GLOB_RECURSE HDRS *.h)

add_library(Engine STATIC ${SRCS} ${HDRS})

set_target_properties(
    Engine PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

# Defines
add_definitions(-D"GLEW_STATIC")
add_definitions(-D"GLM_FORCE_SWIZZLE")
add_definitions(-D"_NO_DEBUG_HEAP=1")
add_definitions(-D"ENTT_API_IMPORT")

# Libraries
target_link_libraries(Engine spdlog)
target_link_libraries(Engine stb_image)

# Include directories
target_include_directories(
    Engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/src/loader
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/renderer_core

    ${CMAKE_SOURCE_DIR}/dependencies/stb_image
    ${CMAKE_SOURCE_DIR}/dependencies/glew/include
    ${CMAKE_SOURCE_DIR}/dependencies/glm/include
    ${CMAKE_SOURCE_DIR}/dependencies/spdlog/include
    ${CMAKE_SOURCE_DIR}/dependencies/entt/include
    ${CMAKE_SOURCE_DIR}/dependencies/nlohmann_json/include
    ${CMAKE_SOURCE_DIR}/dependencies/assimp/include
    ${CMAKE_SOURCE_DIR}/dependencies/glm-aabb/include
)

# Libraries directories
target_link_directories(
    Engine PUBLIC
    ${CMAKE_SOURCE_DIR}/dependencies/SDL2/lib
    ${CMAKE_SOURCE_DIR}/dependencies/glew/lib
    ${CMAKE_SOURCE_DIR}/dependencies/assimp/lib
)

# PCH
target_precompile_headers(
    Engine PUBLIC
    ${CMAKE_SOURCE_DIR}/dependencies/spdlog/include/spdlog/spdlog.h
    ${CMAKE_SOURCE_DIR}/dependencies/spdlog/include/spdlog/sinks/stdout_color_sinks.h
    ${CMAKE_SOURCE_DIR}/dependencies/glm/include/glm/glm.hpp
    ${CMAKE_SOURCE_DIR}/dependencies/glew/include/GL/glew.h
    ${CMAKE_SOURCE_DIR}/dependencies/entt/include/entt/entt.hpp
    ${CMAKE_SOURCE_DIR}/dependencies/nlohmann_json/include/nlohmann/json.hpp
    ${CMAKE_SOURCE_DIR}/dependencies/SDL2/include/SDL2/SDL.h
    <string>
    <vector>
    <memory>
    <unordered_map>
    <exception>
    <utility>
    <algorithm>
)

if (WIN32)
    
    target_include_directories(
        Engine PUBLIC
        ${CMAKE_SOURCE_DIR}/dependencies/SDL2/include
    )

    target_link_libraries(
        Engine
        SDL2.lib
        assimp-vc142-mt.dll
        
        SDL2main.lib
        glew32s.lib
        opengl32.lib
    )
else()
    message(FATAL, "Platfrom not supported")
endif()

