set(CMAKE_POSITION_INDEPENDENT_CODE ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)


add_executable(libSocketCan ./src/socketcan.cpp)
target_include_directories(libSocketCan PUBLIC)

