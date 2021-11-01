cmake_minimum_required(VERSION 3.16)
project(Lab4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

add_executable(Lab4 Ship.h Ship.cpp TestShip.cpp)
target_link_libraries(Lab4 gtest gtest_main)
