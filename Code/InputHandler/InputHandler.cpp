#include "include/InputHandler.hpp"
#include "../libSocketCan/include/socketcan.hpp"

int main(/*int argc, char ** argv*/){
    UserInput user;
    int input;
    while(user.IsRunning()){
        input = getch();
        user.Sensing(input);
        user.ValuesToCan();
        user.PrintSensorValues();
    }
    endwin();
    return 0;
}