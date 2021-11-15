#include <iostream>
#include "../include/emulator.hpp"

bool Emulator::setgearPosition(gearPosition_t currentGearPos)
{
    gearPosition = currentGearPos;
    return true;
}

Emulator::gearPosition_t Emulator::getGearPosition()
{
    return gearPosition;
}

bool Emulator::setGaspedalPostion(int gaspdedalPos)
{
    bool success = false;

    if (gaspdedalPos >= 0 && gaspdedalPos <= 100)
    {
        gaspedalPosition = gaspdedalPos;
        success = true;
    }
    else
    {
        success = false;
    }

    return success;
}
int Emulator::getGaspedalPositon()
{
    return gaspedalPosition;
}

int Emulator::getEngineRPM()
{
    return engineRPM;
}

bool Emulator::setEngineRPM(int RPMValue)
{
    bool success = false;
    if (RPMValue >= 0 && RPMValue <= 5000)
    {
        engineRPM = RPMValue;
        success = true;
    }
    else
    {
        success = false;
    }
    return success;
}
    
 void Emulator::outputRpm(int rpm){
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
