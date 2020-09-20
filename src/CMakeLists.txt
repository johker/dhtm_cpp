cmake_minimum_required(VERSION 3.13)

# Run with cmake -DCMAKE_PREFIX_PATH=~/miniconda3 ..

project(dhtmcore)

set(CMAKE_BUILD_TYPE Debug)

add_library(comlib OBJECT)
add_library(dhtm::comlib ALIAS comlib)

add_library(htmlib OBJECT)
add_library(dhtm::htmlib ALIAS htmlib)

add_library(utilslib OBJECT)
add_library(dhtm::utilslib ALIAS utilslib)

find_library(zmq REQUIRED)
message("ZeroMQ_INCLUDE_DIR  = ${ZeroMQ_INCLUDE_DIR}")
message("ZeroMQ_LIBRARY  = ${ZeroMQ_LIBRARY}")

add_subdirectory(htm)
add_subdirectory(com)
add_subdirectory(utils)

add_executable(dhtmcore main.cpp)

target_link_libraries(dhtmcore
	PUBLIC
		comlib
		htmlib
		utilslib
		${ZeroMQ_LIBRARY}
)
