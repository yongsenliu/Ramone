#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>

class UserInput{
    private: 
        int accPedalPos;
        char gearLever;
        bool sensorRunning;

    public:
        UserInput();
        int getAccPedalPos();
        void Sensing(int input);
        void PrintSensorValues();
        bool IsRunning();
};

void inputWindowInit();


#endif // INPUTHANDLER_HPP
