cmake_minimum_required(VERSION 3.16)
project(Lab3_External)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

add_executable(Lab3_External Vector.cpp Vector.h Dialog.h Dialog.cpp main.cpp)
target_link_libraries(Lab3_External gtest gtest_main)
