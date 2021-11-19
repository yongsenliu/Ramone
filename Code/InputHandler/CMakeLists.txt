set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

add_executable(InputHandler 
		main.cpp
		./src/InputHandler.cpp
		../libSocketCan/src/socketcan.cpp)

target_include_directories(InputHandler PUBLIC 
				./libSocketCan/include
				./InputHandler/include)
target_link_libraries(InputHandler PUBLIC curses)


