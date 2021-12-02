cmake_minimum_required(VERSION 3.5.1)
project(Ramone)

include_directories(../Code/InputHandler/include)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)
enable_testing()

add_executable(testInputHandler testInputHandler.cpp ../Code/InputHandler/src/InputHandlerSource.cpp)
add_executable(testEmulator ./testEmulator.cpp ../Code/Emulator/src/EmulatorSource.cpp)

target_link_libraries(testInputHandler PUBLIC SocketCan curses gtest_main)
target_link_libraries(testEmulator pthread SocketCan gtest_main)

# add_custom_command(TARGET testEmulator POST_BUILD COMMAND /bin/sh ../../setvcan.sh)
# gtest_discover_tests(testEmulator)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
