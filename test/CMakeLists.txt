cmake_minimum_required(VERSION 3.13)                                                                                                                                                                               
# Run with cmake -DCMAKE_PREFIX_PATH=~/miniconda3 ..

project(dhtmtest)

set(CMAKE_BUILD_TYPE Debug)

find_package(xtl REQUIRED)
find_package(xtensor REQUIRED)
find_package(GTest REQUIRED)

find_library(zmq REQUIRED)

add_executable(dhtmtest main.cpp)

target_link_libraries(dhtmtest PUBLIC GTest::GTest GTest::Main zmq xtensor)
