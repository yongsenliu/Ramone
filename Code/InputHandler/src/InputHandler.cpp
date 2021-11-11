#include "../include/InputHandler.hpp"

void inputWindowInit(){
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
}

UserInput::UserInput(){
    this->accPedalPos = 0;
    this->gearLever = 'N';
    this->sensorRunning = true;
    printw("Gear lever and acceleration pedal is up and running. Acceleration pedal position is ");
    printw("%d", accPedalPos);
    printw(" %%");
    printw(" and Gearlever is in ");
    printw("%c", gearLever);
    printw(" position. To accelerate use UP-key and deaccelerate use DOWN-key. To change the gear lever press [p/d/n/r]-keys. To turn off press s-key.\n");

}

void UserInput::PrintSensorValues(){
    std::cout << "The position of the acceleration pedal is: " << accPedalPos << std::endl << "\r";
    std::cout << "The position of the gear lever is: " << gearLever << std::endl << "\r";

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
        this->gearLever = 'P';
        break;
    case 100:
        this->gearLever = 'D';
        break;
    case 110:
        this->gearLever = 'N';
        break;
    case 114:
        this->gearLever = 'R';
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