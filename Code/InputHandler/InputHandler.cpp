#include "include/InputHandler.hpp"
#include "../libSocketCan/include/socketcan.hpp"

int main(/*int argc, char ** argv*/){
    UserInput user;
    int input;
    while(true){
        input = getch();
        user.Sensing(input);
        user.ValuesToCan();
        user.PrintSensorValues();
        if (user.terminator()) {
            user.ValuesToCan();
            return 0;
        }
    }
    endwin();
    std::cout << "The input handler is now terminated!";
    return 0;
}