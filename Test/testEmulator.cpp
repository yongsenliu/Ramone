#include "emulator.hpp"
#include <gtest/gtest.h>

Emulator myEmulator;

// Test method ignition.
TEST (emulator, Ignition){
  // Expect that gearPosition of N (Neutral) true.
  EXPECT_TRUE(myEmulator.ignitionOn());
}