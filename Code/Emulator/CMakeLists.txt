 set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)
#Emulator
add_executable(Emulator 
		main.cpp
		./src/emulator.cpp
		../libSocketCan/src/socketcan.cpp
		)

target_include_directories(Emulator PUBLIC 
				./libSocketCan/include
				./Emulator/include)
target_link_libraries(Emulator PUBLIC pthread)

