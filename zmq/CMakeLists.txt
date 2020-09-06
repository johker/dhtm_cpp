cmake_minimum_required(VERSION 3.13)                                                                                                                                                                               
# Run with cmake -DCMAKE_PREFIX_PATH=~/miniconda3 ..

project(zmqbroker)

set(CMAKE_BUILD_TYPE Debug)

find_library(zmq REQUIRED)

add_executable(zmqbroker main.cpp)

target_link_libraries(zmqbroker 
	PUBLIC 
		zmq
)


