set(CMAKE_POSITION_INDEPENDENT_CODE ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

#set(SocketCan "SocketCan")


#set(PUBLIC_HDRS include/socketcan.hpp)

#set(SRCS src/socketcan.cpp)

#add_library(${SocketCan} ${SHARED_HDRS} ${SRCS})
#add_library(::${SocketCan} ALIAS ${SocketCan}) #Who uses the CMakeLists.txt in libSocketCAN and where alias is used? And Properties?
#if (BUILD_SHARED_LIBS)
#    set_target_properties(${SocketCan} PROPERTIES CXX_VISIBILITY_PRESET hidden)
#    set_target_properties(${SocketCan} PROPERTIES VISIBILITY_INLINES_HIDDEN 1)
#endif()

#target_link_libraries(SocketCan ${PUBLIC_HDRS} curses)
#feedback regarding the libSocketCan: Make it a shared object, either dynamic or static.

add_library(SocketCan SHARED src/socketcan.cpp)

target_include_directories(SocketCan PUBLIC include)


