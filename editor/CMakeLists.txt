cmake_minimum_required(VERSION 3.12)
project(Editor VERSION 0.0.0)

set(EDITOR_IMGUI_LAYER
    imgui_layer/imgui_layer.cpp
    imgui_layer/imgui_layer.h
)

set(EDITOR_SDL_WINDOW
    sdl_window/sdl_window.cpp
    sdl_window/sdl_window.h
)

set(EDITOR_VIEWPORT
    viewport/viewport.cpp
    viewport/viewport.h
)

set(SOURCES
    editor.cpp
    ${EDITOR_IMGUI_LAYER}
    ${EDITOR_SDL_WINDOW}
    ${EDITOR_VIEWPORT}
 )

add_executable(Editor ${SOURCES} "viewport/viewports.h" "viewport/viewports.cpp")

#engine
target_link_libraries(Editor Engine)

# imgui
target_link_libraries(Editor imgui)

set_target_properties(
    Editor PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# include directories
target_include_directories(
    Editor 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../imgui
)