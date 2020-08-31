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

set(ENGINE_INPUT
    src/core/input/input.h
    src/core/input/input.cpp
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

set(RENDERER
    src/renderer/renderer/renderer.h
    src/renderer/renderer/renderer.cpp
)

set(RENDERER_MODEL
    src/renderer/model/mesh.h
    src/renderer/model/mesh.cpp
    src/renderer/model/model.h
)


# Scene
set(SCENE
    src/scene/scene.h
    src/scene/scene.cpp
)

set(SCENE_ENTITY
    src/scene/entity/Entity.h
    src/scene/entity/Entity.cpp
)

set(SCENE_COMPONENTS
    src/scene/components/basic_components.h
)

set(SCENE_SCRIPTABLE_ENTITY
    src/scene/entity/scriptable_entity.h
)


set(SOURCES
    ${ENGINE_APPLICATION}
    ${ENGINE_LAYERS}
    ${ENGINE_LOG}
    ${ENGINE_DELTATIME}
    ${ENGINE_INPUT}

    ${RENDERER_FRAMEBUFFER}
    ${RENDERER_SHADER}
    ${RENDERER_CAMERA}
    ${RENDERER_BUFFER}
    ${RENDERER_VERTEX_ARRAY}
    ${RENDERER_TEXTURE}
    ${RENDERER}
    ${STB_IMAGE}
    ${RENDERER_MODEL}

    ${SCENE}
    ${SCENE_ENTITY}
    ${SCENE_SCRIPTABLE_ENTITY}
)

add_library(Engine STATIC ${SOURCES})

set_target_properties(
    Engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# OpenGL
find_package( OpenGL REQUIRED )
include_directories( ${OPENGL_INCLUDE_DIRS} )
target_link_libraries(Engine ${OPENGL_LIBRARIES} )

target_link_libraries(Engine assimp)
target_link_libraries(Engine spdlog)

if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_link_libraries(Engine glewd)
else()
    target_link_libraries(Engine glew)
endif()



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
    ${CMAKE_CURRENT_BINARY_DIR}/../lib
)


# SDL
if (APPLE)

    target_include_directories(
        Engine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/SDL2/include_macos
    )
    
    target_link_libraries(
        Engine
        libSDL2-2.0.dylib
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
)

endif()
