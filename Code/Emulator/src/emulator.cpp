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
        gasPedalPosition = gaspdedalPos;
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
    return gasPedalPosition;
}

int Emulator::getEngineRPM()
{
    return engineRPM;
}

bool Emulator::ignitionOn() {
    if (ignition == ON) {
        return true;
    }else {
        return false;
    }
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

void Emulator::updateRpm() {
    const std::lock_guard<std::mutex> lock(mu);
    float rate = (MAX_SPD * gasPedalPosition) / 100;

    if (engineRPM < rate){
        engineRPM += rate/100;

    } else if (engineRPM > rate) {
        engineRPM -= rate/100;

    }
    outputRpm();
}


    
void Emulator::outputRpm()
{
    //const std::lock_guard<std::mutex> lock(mu);
    // float indicator = MAX_SPD / engineRPM;
    // while (indicator < 1.0) {
    //     int barWidth = 70;
    //     std::cout << "[";
    //     int pos = barWidth * indicator;
    //     for (int i = 0; i < barWidth; ++i) {
    //         if (i < pos) std::cout << "|";
    //         else if (i == pos) std::cout << ">";
    //         else std::cout << " ";
    //     }
    //     std::cout << "] " << int(indicator * 100.0) << " RPM\r";
    //     std::cout.flush();
    // }
    std::cout << engineRPM << std::endl;
}

void Emulator::canReader(){
    scpp::SocketCan sockat_can;
    
    if (sockat_can.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }

    while (ignitionOn()) {
        scpp::CanFrame fr;
        if (sockat_can.read(fr) == scpp::STATUS_OK) {
            printf("len %d byte, id: %d, data: %02x %02x %02x \n", fr.len, fr.id, 
                fr.data[0], fr.data[1], fr.data[2]);
            const std::lock_guard<std::mutex> lock(mu);
            this->gasPedalPosition = int(fr.data[0]);
            this->gearPosition = gearPosition_t(fr.data[1]);   
            this->ignition = ignition_t(fr.data[2]);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    }
}

void Emulator::canSender() {
    scpp::SocketCan sockat_can1;
    if (sockat_can1.open("vcan1") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan1." << std::endl;
        std::cout << "Check whether the vcan1 interface is up!" << std::endl;
        exit (-1);
    }
    int a[3];
    const std::lock_guard<std::mutex> lock(mu);
    a[0] = int(engineRPM)/256;
    a[1] = int(engineRPM)%256;
    a[2] = 0;
    sockat_can1.send(a,3);
}
