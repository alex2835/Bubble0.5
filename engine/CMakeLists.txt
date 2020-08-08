cmake_minimum_required(VERSION 3.12)

project(engine VERSION 0.0.0)

# Engine core API
set(ENGINE_APPLICATION
    core/application/application.cpp
    core/application/application.h
)

set(ENGINE_LAYERS
    core/layers/layer.cpp
    core/layers/layer.h
    core/layers/layer_array.cpp
    core/layers/layer_array.h
)

set(ENGINE_LOG
    core/log/log.cpp
    core/log/log.h
)

# Renderer
set(RENDERER_FRAMEBUFFER
    renderer/framebuffer/framebuffer.cpp
    renderer/framebuffer/framebuffer.h
)

set(RENDERER_BUFFER
    renderer/buffer/buffer.h
    renderer/buffer/buffer.cpp
)


set(SOURCES
    ${ENGINE_APPLICATION}
    ${ENGINE_LAYERS}
    ${ENGINE_LOG}

    ${RENDERER_FRAMEBUFFER}
)

add_library(Engine STATIC ${SOURCES})

set_target_properties(
    Engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# include directories
target_include_directories(
    Engine 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/core
    ${CMAKE_CURRENT_SOURCE_DIR}/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/GLEW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/spdlog/include
)

# libraris directories
target_link_directories(
    Engine 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL2/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glew/lib
)


if (APPLE)

    target_include_directories(
        Engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL2/include_macos
    )
    
    target_link_libraries(
        Engine
        libSDL2-2.0.dylib
        libGLEW.a
        "-framework OpenGL"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework Carbon"   
    )
endif()


if (WIN32)
    target_include_directories(
        Engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL2/include_win32
    )

    target_link_libraries(
        Engine
        SDL2.dll
        SDL2.lib
        SDL2main.lib
        glew32s.lib
        opengl32.lib
)

endif()
