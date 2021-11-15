#include "include/InputHandler.hpp"
#include "../libSocketCan/include/socketcan_cpp.h"

int main(/*int argc, char ** argv*/){
    inputWindowInit();
    UserInput user;
    scpp::SocketCan sockat_can;
    if (sockat_can.open("vcan0") != scpp::STATUS_OK){
        printw("Could not initialize CAN-network");
    }

    scpp::CanFrame cf_to_write;
    int canId = 100, canFrameLength = 2;
    setupCanFrame(cf_to_write, canId, canFrameLength);

    int input;
    while(user.IsRunning()){
        input = getch();
        user.Sensing(input);
        cf_to_write.data[0] = user.getAccPedalPos();
        cf_to_write.data[1] = user.getGearLeverPosition();
        user.PrintSensorValues();
        auto write_sc_status = sockat_can.write(cf_to_write);
        if (write_sc_status != scpp::STATUS_OK){
            std::cout << "something went wrong on socket write, error code :" << int32_t(write_sc_status) << "\n\r";
        }else{
            std::cout << "Message was written to the socket \n\r";
        }
    }
    endwin();
    return 0;
}