cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 1.0.0)

set(SOURCES
    #engine
    application/application.cpp
    frambuffer/framebuffer.cpp
    layers/layer.cpp
    layers/layer_array.cpp
    log/log.cpp

    #sendbox
    sandbox.cpp
    imgui_layer/imgui_layer.cpp
    sdl_window/sdl_window.cpp

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

# add libraries
target_include_directories(
    bubble 
    PRIVATE
    #inlcude dir
    ${CMAKE_CURRENT_SOURCE_DIR}/src/engine
    ${CMAKE_CURRENT_SOURCE_DIR}/src/sandbox

    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/GLEW/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/SDL2/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/glm/include
    ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/spdlog/include
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