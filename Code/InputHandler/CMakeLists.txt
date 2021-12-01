set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

include_directories(include)
include_directories(../libSocketCan)

add_executable(InputHandler 
		InputHandler.cpp
		./src/InputHandlerSource.cpp
		)

target_include_directories(InputHandler PUBLIC 
				./libSocketCan/include
				./InputHandler/include)

target_link_libraries(InputHandler PUBLIC SocketCan curses)
