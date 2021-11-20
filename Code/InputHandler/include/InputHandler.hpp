#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>
#include "../../libSocketCan/include/socketcan.hpp"

enum GearLever{P,D,N,R};
enum Ignition{Off,On};

class UserInput{
    private: 
        int accPedalPos = 0;
        GearLever gearLeverPos = N;
        //bool sensorRunning = true;
        Ignition ignition = On;
        scpp::SocketCan sockat_can;

    public:
        UserInput();
        int getAccPedalPos();
        void Sensing(int input);
        void PrintSensorValues();
        bool IsRunning();
        void ValuesToCan();
        GearLever getGearLeverPosition();
};

void inputWindowInit();

#endif // INPUTHANDLER_HPP
