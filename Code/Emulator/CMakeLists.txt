cmake_minimum_required(VERSION 3.0.0)
project(BuildEmulatorBinaries)

# GoogleTest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(emulator ./main.cpp ./src/emulator.cpp ../libSocketCan/src/socketcan_cpp.cpp)
add_executable(testEmulator ./testEmulator.cpp ./src/emulator.cpp ../libSocketCan/src/socketcan_cpp.cpp)

target_link_libraries(
  emulator
  pthread
)

target_link_libraries(
  testEmulator
  pthread
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(testEmulator)
