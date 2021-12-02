set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

include_directories(../../libSocketCan/include/)
include_directories(include)
include_directories(../include/)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_executable(InputHandler InputHandler.cpp ./src/InputHandlerSource.cpp)
target_include_directories(InputHandler PUBLIC ./libSocketCan/include ./InputHandler/include)
target_link_libraries(InputHandler PUBLIC SocketCan curses)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
