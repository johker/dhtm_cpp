cmake_minimum_required(VERSION 3.13)                                                                                                                                                                               

# Run with cmake -DCMAKE_PREFIX_PATH=~/miniconda3 ..

project(dhtmcore)

set(CMAKE_BUILD_TYPE Debug)

add_library(dhtmlib)
add_library(utilslib)

find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)

find_library(zmq REQUIRED)

add_subdirectory(dhtm)
add_subdirectory(utils)

add_executable(dhtmcore main.cpp)

target_link_libraries(dhtmcore 
	PUBLIC 
		dhtmlib 
		utilslib 
		xtensor 
		${CURSES_LIBRARY}
)

