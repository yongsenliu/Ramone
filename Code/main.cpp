#include <iostream>
#include "time.h"
#include <thread>
#include <future>

#include "Emulator_debugging/include/emu.hpp"
#include "InputHandler/include/InputHandler.hpp"


void getKey(std::promise<int> &prms) {
    int key = getch();
    prms.set_value(key);
}

int main(/*int argc, char ** argv*/){

    Emu emu;
    UserInput userInput;
    inputWindowInit();

    int input;
    printw("START...");

    while (true)
    {
        clock_t current = clock();
        std::promise<int> prms;
        auto ftr = prms.get_future();

        std::thread thrIn(&getKey, std::ref(prms));

        input = ftr.get();
        thrIn.join();

        userInput.Sensing(input);

        userInput.PrintSensorValues();

        int acc = userInput.getAccPedalPos();

        std::cout << acc << std::endl;

        emu.currentTime = current;
        std::cout << current << std::endl;
        std::cout << emu.currentTime << std::endl;

        emu.setAccPedalPos(acc);

        emu.updateRpm(emu.getAccPedalPos());

        emu.lastTick = current;
        for(int i =0; i<100000; i++) {

        }
    }
    return 0;
}