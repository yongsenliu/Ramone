#include <iostream>
#include "time.h"
#include "emu.hpp"
#include "InputHandler/include/InputHandler.hpp"

int main(/*int argc, char ** argv*/){

    Emu emu;
    UserInput userInput;
    inputWindowInit();

    int input;
    printw("START...");

    while (true)
    {
        clock_t current = clock();
        //input = getch();
        userInput.Sensing(input);

        userInput.PrintSensorValues();

        int acc = userInput.getAccPedalPos();

        std::cout << acc << std::endl;

        emu.currentTime = current;
        std::cout << current << std::endl;
        std::cout << emu.currentTime << std::endl;

        //emu.setAccPedalPos(acc);

        //emu.updateRpm(emu.getAccPedalPos());

        //emu.lastTick = current;
        for(int i =0; i<100000; i++) {

        }
    }
    return 0;
}