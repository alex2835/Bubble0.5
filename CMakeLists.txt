cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 0.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	SET(GCC_COVERAGE_COMPILE_FLAGS "-O0 -w -MP ")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
	set(CMAKE_CXX_FLAGS "-O2 -w -MP -EHsc")
else()
	message(FATAL_ERROR "Please set variable: CMAKE_BUILD_TYPE (Debug or Release)")
endif()


add_subdirectory(editor)
add_subdirectory(engine)

add_subdirectory(dependencies/nativefiledialog)
add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/imgui)
add_subdirectory(dependencies/stb_image)

