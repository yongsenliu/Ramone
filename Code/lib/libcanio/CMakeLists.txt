#considered bad practice
# file(GLOB libcanio_src "src/*.cpp")
# add_library(canio STATIC ${libcanio_src})
# set_target_properties(canio PROPERTIES
#   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/lib/libcanio.a"
#   INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/include"
# )
# target_include_directories(canio PUBLIC include/canio)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

set(canio "canio")
#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

set(PUBLIC_HDRS
    ./include/canio/canio.h
)

set(SRCS 
    ./src/canio.cpp
)

add_library(${canio} ${PUBLIC_HDRS} ${SRCS})
add_library(::${canio} ALIAS ${canio})
if (BUILD_SHARED_LIBS)
    set_target_properties(${canio} PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties(${canio} PROPERTIES VISIBILITY_INLINES_HIDDEN 1)
endif()
