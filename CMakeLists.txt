cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )
set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )

#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

add_subdirectory(Code)
#warnings as errors? A response to "Set warning in your cmake!" feedback
#add_compile_options(-Wall -Wextra -pedantic -Werror)
