
#include "./include/emulator.hpp"
#include <gtest/gtest.h>

Emulator myEmulator;

// Test method setGaspedalPosition.
TEST(emulator, setGaspedalPostion) {
  // Expect that gaspedelposition of 45% ok(true).
    EXPECT_TRUE(myEmulator.setGaspedalPostion(45));

  //Expect that gaspedelposition of 101% false
    EXPECT_FALSE(myEmulator.setGaspedalPostion(101));

//Expect that gaspedelposition of -1% false
    EXPECT_FALSE(myEmulator.setGaspedalPostion(-1));

  //Expect that gaspedelposition of 0% true
    EXPECT_TRUE(myEmulator.setGaspedalPostion(0));

//Expect that gaspedelposition of 100% true
    EXPECT_TRUE(myEmulator.setGaspedalPostion(100));
}

// Test method setgearPosition.
TEST (emulator, setgearPosition){
  // Expect that gearPosition of N (Neutral) true.
  EXPECT_TRUE(myEmulator.setgearPosition(N));

  // Expect that gearPosition of R (Reverse) true.
  EXPECT_TRUE(myEmulator.setgearPosition(R));

  // Expect that gearPosition of D (Drive) true.
  EXPECT_TRUE(myEmulator.setgearPosition(D));

  // Expect that gearPosition of P (Parking) true.
  EXPECT_TRUE(myEmulator.setgearPosition(P));
}