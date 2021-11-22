#include <iostream>
#include <chrono>
#include <thread>
#include "../libSocketCan/include/socketcan_cpp.h"
#include "./include/emulator.hpp"

int main() {
    Emulator myEmulator;

    std::thread t1(&Emulator::canReader, &myEmulator);

    while(myEmulator.ignitionOn()) {
        //myEmulator.updateRpm();
        myEmulator.run();
        myEmulator.canSender();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        // std::cout << "In main thread accpedalPos: " << myEmulator.getGaspedalPositon() << "\n";
        // std::cout << "In main thread gearPosition: " << myEmulator.getGearPosition() << "\n";

    }
    t1.join();
    return 0;
}