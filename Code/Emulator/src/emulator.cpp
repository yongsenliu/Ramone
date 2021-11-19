#include <iostream>
#include "../include/emulator.hpp"
#include "../../libSocketCan/include/socketcan.hpp"
#include <thread>

bool Emulator::setgearPosition(gearPosition_t currentGearPos)
{
    gearPosition = currentGearPos;
    return true;
}

gearPosition_t Emulator::getGearPosition()
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
    
 void Emulator::outputRpm(int rpm)
 {
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

// void Emulator::canReader(int *accPedalPos, gearPosition_t *gearPosition){
void Emulator::canReader(){
    scpp::SocketCan sockat_can;
    
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }
    while (true) {
        scpp::CanFrame fr;
        if (sockat_can.read(fr) == scpp::STATUS_OK) {
            printf("len %d byte, id: %d, data: %02x %02x \n", fr.len, fr.id, 
                fr.data[0], fr.data[1]);
            this->gaspedalPosition = int(fr.data[0]);
            this->gearPosition = gearPosition_t(fr.data[1]);         
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));


    }
}
