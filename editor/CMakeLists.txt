cmake_minimum_required(VERSION 3.12)
project(Editor VERSION 0.0.0)


set(EDITOR_LAYER
    src/editor_layer/editor_layer.cpp
    src/editor_layer/editor_layer.h
)

set(EDITOR_GUI
    src/imgui_controll/imgui_controll.cpp
    src/imgui_controll/imgui_controll.h
)

set(EDITOR_SDL_WINDOW
    src/sdl_window/sdl_window.cpp
    src/sdl_window/sdl_window.h
)

set(EDITOR_VIEWPORT
    src/viewport/viewport.cpp
    src/viewport/viewport.h
    src/viewport/viewport_array.cpp
    src/viewport/viewport_array.h
)

set(SCENE_CAMERA
    src/scene_camera/scene_camera_controller.cpp
    src/scene_camera/scene_camera_controller.h
)

set(SOURCES
    "src/editor_app.cpp"
    ${EDITOR_GUI}
    ${EDITOR_LAYER}
    ${EDITOR_VIEWPORT}
    ${EDITOR_SDL_WINDOW}
    ${SCENE_CAMERA}
 )

add_executable(Bubble ${SOURCES})

# engine
target_link_libraries(Bubble Engine)

# imgui
target_link_libraries(Bubble imgui)


set_target_properties(
    Bubble PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# include directories
target_include_directories(
    Bubble
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../engine/src
    ${CMAKE_CURRENT_SOURCE_DIR}/../dependencies/imgui  
)


add_custom_command(TARGET Bubble PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${PROJECT_SOURCE_DIR}/resources
                       $<TARGET_FILE_DIR:Bubble>/resources)

# put dll with exe
if (WIN32)
    add_custom_command(TARGET Bubble POST_BUILD							# Adds a post-build event to MyTest
        COMMAND ${CMAKE_COMMAND} -E copy_if_different					# which executes "cmake - E copy_if_different..."
            "${PROJECT_SOURCE_DIR}/../dependencies/SDL2/lib/SDL2.dll"   # <--this is in-file
            $<TARGET_FILE_DIR:Bubble>)									# <--this is out-file path
endif()
