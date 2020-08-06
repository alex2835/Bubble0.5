cmake_minimum_required(VERSION 3.12)
project(Bubble VERSION 0.0.0)

if(CMAKE_BUILD_TYPE MATCHES Debug)
	message("--- Debug ---")
	#set release compiler flags 
	SET(GCC_COVERAGE_COMPILE_FLAGS "-O0 -Wall")
elseif (CMAKE_BUILD_TYPE MATCHES Release)
	message("--- Release ---")
	#set release compiler flags 
	set(CMAKE_CXX_FLAGS "-O2 -Wall")
	set(CMAKE_INSTALL_PREFIX ${IMGUI_SOURCES}"/build/Release")
else()
	message(FATAL_ERROR "Not Debug and not Release : " ${CMAKE_BUILD_TYPE})
endif()

# append compiler flags
#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
#SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")
#add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_subdirectory(imgui)
add_subdirectory(engine)
add_subdirectory(editor)
