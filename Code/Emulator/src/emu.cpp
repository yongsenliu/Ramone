#include <iostream>
#include "emu.hpp"

#define ACC_RATE 8.0
#define MAX_SPD 120
#define UPDATE_RATE 10 //10ms

int Emu::getAccPedalPos() {
    //To get data from input handler
}

void Emu::updateRpm(int acc) {
    float rate = (MAX_SPD * ACC_RATE) / 100;
    // currentTime = 
}

void Emu::outputRpm(int rpm) {
     
}