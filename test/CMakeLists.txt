cmake_minimum_required(VERSION 3.13)                                                                                                                                                                               
project(dhtmtest)

add_library(testlib 
	OBJECT 
		utils/messageEncoderTest.cpp 
		utils/messageEncoderTest.hpp
)
add_library(dhtm::testlib ALIAS testlib)


target_link_libraries(testlib 
	PUBLIC 
		GTest::Main 
		zmq 
		xtensor
)
 
set(CMAKE_BUILD_TYPE Debug)

find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(GTest REQUIRED)

find_library(zmq REQUIRED)

add_executable(dhtmtest main.cpp)

target_link_libraries(dhtmtest 
	PUBLIC 
		dhtm::testlib
		dhtm::utilslib
)

