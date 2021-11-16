#include <iostream>
#include <chrono>
#include <thread>
#include "../libSocketCan/include/socketcan_cpp.h"
#include "./include/emulator.hpp"

void foo(){
    std::cout << "I am here";
}

int main() {
    Emulator myEmulator;
    int accPedalPos;
    gearPosition_t gearPos;
    std::thread t1(&Emulator::canReader, &myEmulator);
    // std::thread t2(foo);
    
    //t1.detach();
    while(true){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout << "In main thread accpedalPos: " << myEmulator.getGaspedalPositon() << "\n";
        std::cout << "In main thread gearPosition: " << myEmulator.getGearPosition() << "\n";

    }

    t1.join();
}