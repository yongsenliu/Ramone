 set(CMAKE_INCLUDE_CURRENT_DIR ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(Emulator ./Emulator.cpp ./src/EmulatorSource.cpp)
target_link_libraries(Emulator pthread SocketCan)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef ")
