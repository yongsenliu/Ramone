#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <iostream>
#include <ncurses.h>
#include <array> 
#include "socketcan.hpp"
#include "NcKeyBindings.hpp"

enum class GearLever{P,D,N,R};
enum class Ignition{Off,On};
struct UserInputCanData{
    unsigned int accPedalPos;
    GearLever gearLeverPos;
    Ignition ignition;
    int brkPedal;
    bool shutdown;
};

class UserInput{
    private:
        //Constants
        const unsigned int accPedalMax = 100;
        const unsigned int accPedalMin = 0;
        const unsigned int accPedalChange = 5;
        //Variables 
        UserInputCanData canData ={0, GearLever::N, Ignition::Off, 0, false};

    public:
        void Sensing(int input);
        void PrintSensorValues();
        UserInputCanData ValuesToCan();
        bool isTerminated();
};

void initializeWindowAndCan(scpp::SocketCan &socketCan);
void inputAbstractionToCan(int (&a)[5], UserInputCanData values);
void printInstructions();

#endif // INPUTHANDLER_HPP
