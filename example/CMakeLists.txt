cmake_minimum_required(VERSION 2.8)
project(LysTest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(include)

set(SOURCE_FILES main.cpp)
add_executable(LysTest ${SOURCE_FILES})

target_link_libraries(LysTest lys)