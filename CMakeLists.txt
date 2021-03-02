cmake_minimum_required(VERSION 3.16)
project(urrr)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCE_FILES src/*.cpp src/players/*.cpp)

add_executable(ur ${SOURCE_FILES})
