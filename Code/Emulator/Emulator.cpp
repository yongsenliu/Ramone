#include "./include/emulator.hpp"

int main() {
    Emulator myEmulator;
    std::thread t1(&Emulator::canReader, &myEmulator);

    while(myEmulator.ignitionOn()) {
        myEmulator.run();
        myEmulator.canSender();
        std::this_thread::sleep_for(std::chrono::milliseconds(myEmulator.rasterTimeInMiliSeconds()));
    }
    t1.join();
    return 0;
}