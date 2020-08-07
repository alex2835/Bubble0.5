cmake_minimum_required(VERSION 3.12)
project(Editor VERSION 0.0.0)



set(EDITOR_LAYER
    editor_layer/editor_layer.cpp
    editor_layer/editor_layer.h
)

set(EDITOR_GUI
    imgui_controll/imgui_controll.cpp
    imgui_controll/imgui_controll.h
)

set(EDITOR_SDL_WINDOW
    sdl_window/sdl_window.cpp
    sdl_window/sdl_window.h
)

set(EDITOR_VIEWPORT
    viewport/viewport.cpp
    viewport/viewport.h
    viewport/viewports.cpp
    viewport/viewports.h
)

set(SOURCES
    "editor_app.cpp"
    ${EDITOR_GUI}
    ${EDITOR_LAYER}
    ${EDITOR_SDL_WINDOW}
    ${EDITOR_VIEWPORT}
 )

add_executable(Editor ${SOURCES})

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
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine
    ${CMAKE_CURRENT_SOURCE_DIR}/../imgui
)

# put dll with exe
if (WIN32)
    add_custom_command(TARGET Editor POST_BUILD							# Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different					# which executes "cmake - E copy_if_different..."
            "${PROJECT_SOURCE_DIR}/../dependencies/SDL2/lib/SDL2.dll"   # <--this is in-file
            $<TARGET_FILE_DIR:Editor>)									# <--this is out-file path
endif()
