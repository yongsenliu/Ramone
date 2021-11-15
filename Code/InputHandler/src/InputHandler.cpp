#include "../include/InputHandler.hpp"

void inputWindowInit(){
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
}

UserInput::UserInput(){
    this->accPedalPos = 0;
    this->gearLeverPos = N;
    this->sensorRunning = true;
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
        this->sensorRunning = false;
        break;
    default:
        break;
    }
}

bool UserInput::IsRunning(){
    return sensorRunning;
}

int UserInput::getAccPedalPos() {
    return accPedalPos;
}

GearLever UserInput::getGearLeverPosition(){
    return gearLeverPos;
}

void setupCanFrame(scpp::CanFrame & _canFrame, int id, int length){
    _canFrame.id = 100;
    _canFrame.len = 2;
    for(int i =0; i <2; i++){
        _canFrame.data[i] = 0;
    }
}


