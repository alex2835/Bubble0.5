cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 0.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message("--- Debug ---")
	#set release compiler flags 
	SET(GCC_COVERAGE_COMPILE_FLAGS "-O0 -Wall -MP ")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
	message("--- Release ---")
	#set release compiler flags 
if (WIN32)
	# Windows flags
	set(CMAKE_CXX_FLAGS "-O2 -MP -EHsc")
else()
	set(CMAKE_CXX_FLAGS "-O2 -MP")
endif()
	#set(CMAKE_INSTALL_PREFIX "/build/Release")
else()
	message(FATAL_ERROR "Please set variable: CMAKE_BUILD_TYPE (Debug or Release)")
endif()


# Assimp flags
set(BUILD_SHARED_LIBS OFF)
set(DASSIMP_BUILD_ASSIMP_TOOLS OFF)

# Glew flags
set( GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE )
set( GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE )
set(glew-cmake_BUILD_STATIC ON)
set(glew-cmake_BUILD_SHARED OFF)
#set(GLEW_USE_STATIC_LIBS TRUE)

add_subdirectory(dependencies/glew)

add_subdirectory(editor)
add_subdirectory(engine)

add_subdirectory(dependencies/assimp)
add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/imgui)
