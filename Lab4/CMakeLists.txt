cmake_minimum_required(VERSION 3.16)
project(Lab4)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/include)
include_directories(lib/googlemock/include)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)


add_executable(Lab4 Ship.h Ship.cpp Table.h Table.cpp Mission.h Mission.cpp UnordedNode.h Console.h Console.cpp main.cpp Bot.cpp)
target_link_libraries(Lab4 gtest gtest_main)

include_directories(C:/SFML/include)
target_link_libraries(Lab4 sfml-system sfml-window sfml-graphics sfml-audio)