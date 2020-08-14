cmake_minimum_required(VERSION 3.12)

project(engine VERSION 0.0.0)

# Engine core API
set(ENGINE_APPLICATION
    src/core/application/application.cpp
    src/core/application/application.h
)

set(ENGINE_LAYERS
    src/core/layers/layer.cpp
    src/core/layers/layer.h
    src/core/layers/layer_array.cpp
    src/core/layers/layer_array.h
)

set(ENGINE_LOG
    src/core/log/spdlog.cpp
    src/core/log/log.cpp
    src/core/log/log.h
)

set(ENGINE_DELTATIME
    src/core/delta_time/delta_time.cpp
    src/core/delta_time/delta_time.h
)

# Renderer
set(RENDERER_FRAMEBUFFER
    src/renderer/framebuffer/framebuffer.cpp
    src/renderer/framebuffer/framebuffer.h
)

set(RENDERER_BUFFER
    src/renderer/buffer/buffer.h
    src/renderer/buffer/buffer.cpp
)

set (RENDERER_SHADER
    src/renderer/shader/shader.h
    src/renderer/shader/shader.cpp
)

set (RENDERER_CAMERA
    src/renderer/camera/camera.h
    src/renderer/camera/camera.cpp
)

set (RENDERER_VERTEX_ARRAY
    src/renderer/vertex_array/vertex_array.h
    src/renderer/vertex_array/vertex_array.cpp
)

set (RENDERER_TEXTURE
    src/renderer/texture/texture.h
    src/renderer/texture/texture.cpp
)

set (STB_IMAGE
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/stb_image/stb_image.cpp
)

set(RENDERER_RENDERER
    src/renderer/renderer/renderer.h
    src/renderer/renderer/renderer.cpp
)


set(SOURCES
    ${ENGINE_APPLICATION}
    ${ENGINE_LAYERS}
    ${ENGINE_LOG}
    ${ENGINE_DELTATIME}

    ${RENDERER_FRAMEBUFFER}
    ${RENDERER_SHADER}
    ${RENDERER_CAMERA}
    ${RENDERER_BUFFER}
    ${RENDERER_VERTEX_ARRAY}
    ${RENDERER_TEXTURE}
    ${RENDERER_RENDERER}
    ${STB_IMAGE}
)

add_library(Engine STATIC ${SOURCES})

set_target_properties(
    Engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)


target_link_libraries(Engine spdlog)


# include directories
target_include_directories(
    Engine 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/stb_image
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
