#include "InputHandler.hpp"

int main(/*int argc, char ** argv*/){
    scpp::SocketCan socketCan;
    initializeWindowAndCan(socketCan);
    UserInput user;
    printInstructions();
    int input, canData[5], canDataSize = 5, canId = 100;

    while(!user.isTerminated()){
        input = getch();
        user.Sensing(input);
        inputAbstractionToCan(canData, user.ValuesToCan());
        socketCan.send(canData, canDataSize, canId);
        user.PrintSensorValues();
    }
    endwin();
    std::cout << "The input handler is now terminated!"<< std::endl;
    return 0;
}
