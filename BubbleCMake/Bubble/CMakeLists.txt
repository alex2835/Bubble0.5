cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 0.0.0)


file(GLOB SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

set(SOURCES
    #engine
    src/engine/application/application.cpp
    src/engine/framebuffer/framebuffer.cpp
    src/engine/layers/layer.cpp
    src/engine/layers/layer_array.cpp
    src/engine/log/log.cpp
    
    #sendbox
    src/sandbox/sandbox.cpp
    src/sandbox/imgui_layer/imgui_layer.cpp
    src/sandbox/sdl_window/sdl_window.cpp

    #${SOURCE_FILES}

    #imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/imgui_impl_opengl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/imgui_impl_sdl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui/imgui_widgets.cpp
)

set(HEADERS

)

add_executable(bubble ${SOURCES} ${HEADERS})

set_target_properties(
    bubble PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# include directories
target_include_directories(
    bubble 
    PRIVATE
    #inlcude dir
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sandbox

    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog/include
)

# source directories
target_sources(
    bubble
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sandbox
)

target_link_directories(
    bubble 
    PRIVATE
    #lib dir
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/lib
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glew/lib
)

if (APPLE)
    target_link_libraries(
        bubble
        libglfw3.a
        libGLEW.a
        "-framework OpenGL"
        "-framework IOKit"
        "-framework Cocoa"
        "-framework Carbon"
    )
endif()


if (WIN32)
    target_link_libraries(
        bubble
        SDL2.dll
        SDL2.lib
        SDL2main.lib
        glew32s
        opengl32
)
endif()