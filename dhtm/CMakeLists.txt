cmake_minimum_required(VERSION 3.13)                                                                                                                                                                               

# Run with cmake -DCMAKE_PREFIX_PATH=~/miniconda3 ..

project(dhtmcore)

set(CMAKE_BUILD_TYPE Debug)

add_library(utilslib)

find_package(xtl REQUIRED)                                                                                                                                                                                   
find_package(xtensor REQUIRED)
find_package(Curses REQUIRED)

find_library(panel REQUIRED)

add_subdirectory(utils)

add_executable(dhtmcore main.cpp)

target_link_libraries(dhtmcore PUBLIC utilslib panel xtensor ${CURSES_LIBRARY})

