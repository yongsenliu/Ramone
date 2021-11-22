set(CMAKE_POSITION_INDEPENDENT_CODE ON)
cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

set(PUBLIC_HDRS
    include/socketcan.hpp
)

set(SRCS 
    src/socketcan.cpp
)

add_library(${PROJECT_NAME} ${PUBLIC_HDRS} ${SRCS})
add_library(::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
if (BUILD_SHARED_LIBS)
    set_target_properties(${PROJECT_NAME} PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties(${PROJECT_NAME} PROPERTIES VISIBILITY_INLINES_HIDDEN 1)
endif()

# add_executable(libSocketCan ./src/socketcan.cpp)
# target_include_directories(libSocketCan PUBLIC)

