cmake_minimum_required(VERSION 3.12)

project(engine VERSION 0.0.0)

# Engine core API
set(ENGINE_CORE
    src/core/application/application.cpp
    src/core/application/application.h
    src/core/layers/layer.cpp
    src/core/layers/layer.h
    src/core/layers/layer_array.cpp
    src/core/layers/layer_array.h
    src/core/log/spdlog.cpp
    src/core/log/log.cpp
    src/core/log/log.h
    src/core/delta_time/delta_time.cpp
    src/core/delta_time/delta_time.h
    src/core/input/input.h
    src/core/input/input.cpp
)

# Renderer
set(RENDERER
    src/renderer/framebuffer/framebuffer.cpp
    src/renderer/framebuffer/framebuffer.h
    src/renderer/buffer/buffer.h
    src/renderer/buffer/buffer.cpp
    src/renderer/shader/shader.h
    src/renderer/shader/shader.cpp
    src/renderer/camera/camera.h
    src/renderer/camera/camera.cpp
    src/renderer/vertex_array/vertex_array.h
    src/renderer/vertex_array/vertex_array.cpp
    src/renderer/texture/texture.h
    src/renderer/texture/texture.cpp
    src/renderer/renderer/renderer.h
    src/renderer/renderer/renderer.cpp
    src/renderer/model/mesh.h
    src/renderer/model/mesh.cpp
    src/renderer/model/model.h
    src/renderer/model/model_loader.cpp
)

# Rendering stuff
set(RENDERING_STUFF
    src/renderer/light/light.h
    src/renderer/light/light.cpp
    src/renderer/light/light_array.h
    src/renderer/material/material.h
    src/renderer/material/material.cpp
)

# Scene
set(SCENE
    src/scene/scene.h
    src/scene/scene.cpp
    src/scene/entity/Entity.h
    src/scene/entity/Entity.cpp
    src/scene/components/basic_components.h
    src/scene/entity/scriptable_entity.h
)

# stb image
set (STB_IMAGE
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/stb_image/stb_image.cpp
)


set(SOURCES
    ${ENGINE_CORE}
    ${RENDERER}
    ${RENDERING_STUFF}
    ${SCENE}
    ${STB_IMAGE}
)

add_library(Engine STATIC ${SOURCES})

set_target_properties(
    Engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

## OpenGL
#find_package( OpenGL REQUIRED )
#include_directories( ${OPENGL_INCLUDE_DIRS} )
#target_link_libraries(Engine ${OPENGL_LIBRARIES} )
#
#if (CMAKE_BUILD_TYPE MATCHES Debug)
#    target_link_libraries(Engine glewd)
#else()
#    target_link_libraries(Engine glew)
#endif()

target_link_libraries(Engine assimp)
target_link_libraries(Engine spdlog)


# include directories
target_include_directories(
    Engine 
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/core
    ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer
    ${CMAKE_CURRENT_SOURCE_DIR}/src/scene
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/stb_image
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glew/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/glm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/spdlog/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/entt/include
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/assimp/include
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
elseif(WIN32)
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
else()
    message(FATAL, "LINUX NOT SUPPORTED YET")
endif()
