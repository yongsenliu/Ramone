#include <iostream>
#include "../include/emu.hpp"

#define ACC_RATE 8.0
#define MAX_SPD 120
#define UPDATE_RATE 100 //100ms

void Emu::setAccPedalPos(int inputAcc) {
    //To get data from input handler
    currentAccPos = inputAcc;
}

int Emu::getAccPedalPos() {
    return currentAccPos;
}

int Emu::getRpm() {
    return currentEngineRpm;
}

void Emu::updateRpm(int acc) {
    float rate = (MAX_SPD * ACC_RATE) / 100;
    if (currentTime > lastTick + UPDATE_RATE) {
        if (currentAccPos > lastAccPos) {
            currentEngineRpm += rate;
            if (currentEngineRpm > (MAX_SPD * currentAccPos) / 100) {
                currentEngineRpm = (MAX_SPD * currentAccPos) / 100;
            }
        } else if (currentAccPos < lastAccPos) {
            currentEngineRpm -= rate;
            if (currentEngineRpm < (MAX_SPD * currentAccPos) / 100) {
                currentEngineRpm = (MAX_SPD * currentAccPos) / 100;
            }
        }
        outputRpm(currentEngineRpm);
        lastTick = currentTime;
    }
}

void Emu::outputRpm(int rpm) {
    float indicator = MAX_SPD / rpm;
    while (indicator < 1.0) {
        int barWidth = 70;
        std::cout << "[";
        int pos = barWidth * indicator;
        for (int i = 0; i < barWidth; ++i) {
            if (i < pos) std::cout << "|";
            else if (i == pos) std::cout << ">";
            else std::cout << " ";
        }
        std::cout << "] " << int(indicator * 100.0) << " RPM\r";
        std::cout.flush();
    }
    std::cout << std::endl;
}

