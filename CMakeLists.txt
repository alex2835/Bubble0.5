cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 0.0.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose Release or Debug" FORCE)
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message("--- Debug ---")
	#set release compiler flags 
	SET(GCC_COVERAGE_COMPILE_FLAGS "-O0 -Wall -MP")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
	message("--- Release ---")
	#set release compiler flags 
	set(CMAKE_CXX_FLAGS "-O2 -Wall -MP")
	set(CMAKE_INSTALL_PREFIX "/build/Release")
else()
	message(FATAL_ERROR "Please set variable: CMAKE_BUILD_TYPE (Debug or Release)")
endif()

# append compiler flags
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_subdirectory(dependencies/spdlog)
add_subdirectory(dependencies/imgui)
add_subdirectory(engine)
add_subdirectory(editor)
