#include "./include/emulator.hpp"

int main() {
    Emulator myEmulator;
    std::thread t1(&Emulator::canReader, &myEmulator);

    while(/*myEmulator.ignitionOn()*/true) {
        myEmulator.setIgnition();
        if (myEmulator.ignitionOn()) {
            std::cout << "Engine is on." << std::endl;
            //myEmulator.clusterCheck();
            myEmulator.run();
            myEmulator.canSender();
        } else {
            std::cout << "Engine is off." << std::endl;
            myEmulator.canSender_reset();
            myEmulator.isChecked = false;
        }
        myEmulator.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(myEmulator.rasterTimeInMiliSeconds()));
    }
    t1.join();
    return 0;
}