#include <iostream>
#include "time.h"
#include "emu.hpp"
#include "InputHandler.hpp"

int main(/*int argc, char ** argv*/){
    clock_t current = clock();
    Emu emu;
    UserInput userInput;
    inputWindowInit();

    int input;

    while (1)
    {
        input = getch();
        userInput.Sensing(input);

        int acc = userInput.getAccPedalPos();

        emu.currentTime = current;
        
        emu.setAccPedalPos(acc);
        emu.updateRpm(emu.getAccPedalPos());
        // emu.outputRpm(emu.getRpm());

        emu.lastTick = current;
    }
}