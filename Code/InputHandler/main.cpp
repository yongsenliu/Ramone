#include "include/InputHandler.hpp"

int main(/*int argc, char ** argv*/){
    inputWindowInit();
    UserInput user;
    
    int ch;
    while(user.IsRunning()){
        int input = getch();
        user.Sensing(input);
        user.PrintSensorValues();
    }
    endwin();
    return 0;
}