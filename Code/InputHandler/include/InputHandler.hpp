#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>
#include "../../libSocketCan/include/socketcan_cpp.h"

enum GearLever{P,D,N,R};

class UserInput{
    private: 
        int accPedalPos;
        GearLever gearLeverPos;
        bool sensorRunning;

    public:
        UserInput();
        int getAccPedalPos();
        void Sensing(int input);
        void PrintSensorValues();
        bool IsRunning();
        GearLever getGearLeverPosition();
};

void inputWindowInit();

void setupCanFrame(scpp::CanFrame & _canFrame, const int id, const int length);

#endif // INPUTHANDLER_HPP
