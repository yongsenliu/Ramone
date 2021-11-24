cmake_minimum_required(VERSION 3.5.1)
project(Ramone)
option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
# Testing Ramone2

add_subdirectory(Code)
#add_subdirectory(avic)
