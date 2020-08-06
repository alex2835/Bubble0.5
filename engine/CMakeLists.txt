cmake_minimum_required(VERSION 3.12)

project(engine VERSION 0.0.0)

# engine files
set(ENGINE_APPLICATION
    application/application.cpp
    application/application.h
)

set(ENGINE_FRAMEBUFFER
    framebuffer/framebuffer.cpp
    framebuffer/framebuffer.h
)

set(ENGINE_LAYERS
    layers/layer.h
    layers/layer_array.cpp
    layers/layer_array.h
)

set(ENGINE_LOG
    log/log.cpp
    log/log.h
)

set(SOURCES
    ${ENGINE_APPLICATION}
    ${ENGINE_FRAMEBUFFER}
    ${ENGINE_LAYERS}
    ${ENGINE_LOG}
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
