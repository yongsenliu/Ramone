#include "include/InputHandler.hpp"
#include "../libSocketCan/include/socketcan.hpp"

int main(/*int argc, char ** argv*/){
    UserInput user;
    int input;
    while(!user.terminator()){
        input = getch();
        user.Sensing(input);
        user.ValuesToCan();
        user.PrintSensorValues();
    }
    endwin();
    std::cout << "The input handler is now terminated!";
    return 0;
}