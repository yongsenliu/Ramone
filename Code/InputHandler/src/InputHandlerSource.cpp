#include "../include/InputHandler.hpp"

void inputWindowInit(){
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
}

UserInput::UserInput(){
    inputWindowInit();
    if (sockat_can.open("vcan0") != scpp::STATUS_OK){
        printw("Could not initialize CAN-network");
        exit(1);
    }
    printw("Gear lever and acceleration pedal is up and running. Acceleration pedal position is ");
    printw("%d", accPedalPos);
    printw(" %%");
    printw(" and Gearlever is in ");
    printw("%c", gearLeverPos);
    printw(" position. To accelerate use UP-key and deaccelerate use DOWN-key. To change the gear lever press [p/d/n/r]-keys. To turn off press s-key.\n");
}

void UserInput::PrintSensorValues(){
    std::cout << "The position of the acceleration pedal is: " << accPedalPos << std::endl << "\r";
    std::cout << "The position of the gear lever is: " << GearLever(gearLeverPos) << "\n\r";
    std::cout << "Breaking status is: " << brkPedal << "\n\r";
    std::cout << "Ignition key status is: " << ignition << "\n\r";
}

void UserInput::Sensing(int input){
    switch(input){
    case KEY_UP:
        if(accPedalPos < 100){
            this->accPedalPos = accPedalPos + 5;
        }
        break;
    case KEY_DOWN:
        if(accPedalPos > 0){
            this->accPedalPos = accPedalPos - 5;
        }
        break;
    case 112:
        this->gearLeverPos = P;
        break;
    case 100:
        this->gearLeverPos = D;
        break;
    case 110:
        this->gearLeverPos = N;
        break;
    case 114:
        this->gearLeverPos = R;
        break;
    case 115:
        if (this->ignition == Off) {
            this->ignition= On;
        } else if (this->ignition == On) {
            this->ignition = Off;
        }
        
        break;
    case 98:
        if (this->brkPedal == 0) {
            this->brkPedal = 1;
        } else if (this->brkPedal == 1) {
            this->brkPedal = 0;
        }
        break;

    case 27:
        this->isTerminated = true;
        break;

    default:
        break;
    }
}

bool UserInput::IsRunning(){
    if(ignition == On){
        return true;
    } else{
        return false;
    }
}

int UserInput::getAccPedalPos() {
    return accPedalPos;
}

void UserInput::ValuesToCan(){
    int a[5];
    a[0] = accPedalPos;
    a[1] = gearLeverPos;
    a[2] = ignition;
    a[3] = brkPedal;
    a[4] = isTerminated;
    sockat_can.send(a,5);
 }

GearLever UserInput::getGearLeverPosition(){
    return gearLeverPos;
}

bool UserInput::terminator() {
    return isTerminated;
}
