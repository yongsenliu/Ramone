#include "./include/emulator.hpp"

int main() {
    Emulator myEmulator;
    std::thread t1(&Emulator::canReader, &myEmulator);

    while(!myEmulator.terminator()) {
        myEmulator.setIgnition();
        if (myEmulator.ignitionOn()) {
            std::cout << "Engine is on." << std::endl;
            myEmulator.run();
            myEmulator.canSender();
        } else {
            std::cout << "Engine is off." << std::endl;
            myEmulator.canSender_reset();
        }
        myEmulator.print();

        std::this_thread::sleep_for(std::chrono::milliseconds(myEmulator.rasterTimeInMiliSeconds()));
    }

    t1.join();
    std::cout << "The emulator is now terminated!" << std::endl;
    return 0;
}