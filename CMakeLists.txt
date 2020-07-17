cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 0.0.0)

if(CMAKE_BUILD_TYPE EQUAL  "Debug")
	SET(CMAKE_CXX_FLAGS  "-Wall")
	message("Debug\n")
elseif (CMAKE_BUILD_TYPE EQUAL  "Release")
	SET(CMAKE_CXX_FLAGS  "-Wall -O2")
	message("Release\n")
endif()

add_subdirectory(imgui)
add_subdirectory(engine)
add_subdirectory(editor)