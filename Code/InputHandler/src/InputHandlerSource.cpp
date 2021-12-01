#include "../include/InputHandler.hpp"

void initializeWindowAndCan(scpp::SocketCan &socketCan){
    initscr();
    keypad(stdscr, TRUE);
    cbreak();
    noecho();
    if (socketCan.open("vcan0") != scpp::STATUS_OK){
        printw("Could not initialize CAN-network");
        exit(1);
    }
}

void printInstructions(){
    printw("To change the acceleration pedal use Up-key and Down key.\n");
    printw("To change the gear lever position use P-key, D-key, N-key or R-key.\n");
    printw("To apply breaks use B-key.\n");
    printw("To turn the ignition on and off use S-key.\n");
    printw("To shut down the input handler and emulator use Esc-key\n");

}

void UserInput::PrintSensorValues(){
    std::cout << "The position of the acceleration pedal is: " << this->canData.accPedalPos << std::endl << "\r";
    std::cout << "The position of the gear lever is: " << (int)this->canData.gearLeverPos << "\n\r";
    std::cout << "Breaking status is: " << this->canData.brkPedal << "\n\r";
    std::cout << "Ignition key status is: " << (int)this->canData.ignition << "\n\r";
}

void UserInput::Sensing(int input){
    switch(input){
    case KEY_UP:
        if(this->canData.accPedalPos < accPedalMax){
            this->canData.accPedalPos += accPedalChange;
        }
        break;
    case KEY_DOWN:
        if(this->canData.accPedalPos > accPedalMin){
            this->canData.accPedalPos -= accPedalChange;
        }
        break;
    case NC::P_KEY:
        this->canData.gearLeverPos = GearLever::P;
        break;
    case NC::D_KEY:
        this->canData.gearLeverPos = GearLever::D;
        break;
    case NC::N_KEY:
        this->canData.gearLeverPos = GearLever::N;
        break;
    case NC::R_KEY:
        this->canData.gearLeverPos = GearLever::R;
        break;
    case NC::S_KEY:
        if (this->canData.ignition == Ignition::Off) {
            this->canData.ignition = Ignition::On;
        } else if (this->canData.ignition == Ignition::On) {
            this->canData.ignition = Ignition::Off;
        }
        break;
    case NC::B_KEY:
        if (this->canData.brkPedal == 0) {
            this->canData.brkPedal = 1;
        } else if (this->canData.brkPedal == 1) {
            this->canData.brkPedal = 0;
        }
        break;
    case NC::ESC_KEY:
        this->canData.shutdown = true;
        break;
    default:
        break;
    }
}

UserInputCanData UserInput::ValuesToCan(){
    return this->canData;
 }

bool UserInput::isTerminated() {
    return this->canData.shutdown;
}

void inputAbstractionToCan(int (&a)[5], UserInputCanData values){
    a[0] = values.accPedalPos;
    a[1] = static_cast<int>(values.gearLeverPos);
    a[2] = static_cast<int>(values.ignition);
    a[3] = values.brkPedal;
    a[4] = values.shutdown;
}
