cmake_minimum_required(VERSION 3.5.2)
cmake_policy(SET CMP0015 NEW)
project(lys)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -static -std=c++11")

include_directories(include)

add_subdirectory(example)

file(GLOB SOURCE_FILES src/*.cpp include/lys/*.hpp)
add_library(lys STATIC ${SOURCE_FILES})

target_link_libraries(lys http_parser protobuf)