cmake_minimum_required(VERSION 3.16)
project(Bubble VERSION 0.0.0)


add_compile_options(/O0 /w /MP)

set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CMAKE_COMMAND} -E time")

add_subdirectory(editor)
add_subdirectory(engine/core)
add_subdirectory(engine/entt_lib)

add_subdirectory(dependencies/nativefiledialog)
add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/stb_image)
