set(CMAKE_POSITION_INDEPENDENT_CODE ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

set(SocketCan "SocketCan")
#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(PUBLIC_HDRS
    include/socketcan.hpp
)

set(SRCS 
    src/socketcan.cpp
)

add_library(${SocketCan} ${PUBLIC_HDRS} ${SRCS})
add_library(::${SocketCan} ALIAS ${SocketCan})
if (BUILD_SHARED_LIBS)
    set_target_properties(${SocketCan} PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties(${SocketCan} PROPERTIES VISIBILITY_INLINES_HIDDEN 1)
endif()


