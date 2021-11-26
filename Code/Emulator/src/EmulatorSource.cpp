#include "../include/emulator.hpp"

Emulator::Emulator(){
    if (socketCanReader.open("vcan0") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan0." << std::endl;
        std::cout << "Check whether the vcan0 interface is up!" << std::endl;
        exit (-1);
    }

    if (socketCanWriter.open("vcan1") != scpp::STATUS_OK) {
        std::cout << "Cannot open vcan1." << std::endl;
        std::cout << "Check whether the vcan1 interface is up!" << std::endl;
        exit (-1);
    }
}

void Emulator::setIgnition() {
    if ((brkPedal == 1) && (ignition == ON)) {
        isIgnitionOn = true;
    } else if ((vehicleSpeed < 100) && (ignition == OFF)) {
        isIgnitionOn = false;
    }

}

// bool Emulator::ignitionOn() {
//     if (ignition == ON) {
//         return true;
//     }else {
//         return false;
//     }
// }

bool Emulator::ignitionOn() {
    return isIgnitionOn;
}

float absolute(float value){
    if( value < 0){
        return - value;
    }
    return value;
}

int Emulator::rasterTimeInMiliSeconds(){
    return dT * 1000;
}

void Emulator::canReader(){
    while (/*ignitionOn()*/true) {
        scpp::CanFrame fr;
        if (socketCanReader.read(fr) == scpp::STATUS_OK) {
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x \n", fr.len, fr.id, 
                fr.data[0], fr.data[1], fr.data[2], fr.data[3]);
            const std::lock_guard<std::mutex> lock(mu);
            this->gasPedalPosition = int(fr.data[0]);
            this->gearPosition = gearPosition_t(fr.data[1]);   
            this->ignition = ignition_t(fr.data[2]);
            this->brkPedal = int(fr.data[3]);
            this->isTerminated = bool(fr.data[4]);

        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Emulator::canSender() {
    int engineCanData[5];
    const std::lock_guard<std::mutex> lock(mu);
    
    engineCanData[0] = int(engineRPM)%256;
    engineCanData[1] = int(engineRPM)/256;
    
    engineCanData[2] = int(absolute(vehicleSpeed)*2.23694)%256;
    engineCanData[3] = int(absolute(vehicleSpeed)*2.23694)/256;

    engineCanData[4] = 0xff;
    engineCanData[5] = 0xff;
    socketCanWriter.send(engineCanData, 6, 0x123);

    int gearboxCanData[2];
    Gearbx_t g;

    if (gearPosition == P) {
        g.Bits.GEAR_P = 0;
    } else if (gearPosition == N) {
        g.Bits.GEAR_P = 1;
    } else if (gearPosition == D) {
        g.Bits.GEAR_P = 3;
    } else if (gearPosition == R) {
        g.Bits.GEAR_P = 2;
    }

    g.Bits.GEAR_N = gearIndex;
    
    gearboxCanData[0] = g.Data[0];
    gearboxCanData[1] = g.Data[1];

    socketCanWriter.send(gearboxCanData, 2, 0x312);

    int gaugeCanData[3];
    gaugeCanData[0] = 100;
    gaugeCanData[1] = 200;
    gaugeCanData[2] = 50;

    socketCanWriter.send(gaugeCanData, 3, 0x321);


}

void Emulator::canSender_reset() {
    int engineCanDataReset[5];
    engineCanDataReset[0] = 0;
    engineCanDataReset[1] = 0;
    engineCanDataReset[2] = 0;
    engineCanDataReset[3] = 0;
    socketCanWriter.send(engineCanDataReset, 4, 0x123);
    
    int gearboxCanDataReset[2];
    gearboxCanDataReset[0] = 0x00;
    gearboxCanDataReset[1] = 0x00;
    socketCanWriter.send(gearboxCanDataReset, 2, 0x312);

    int gaugeCanDataReset[1];
    gaugeCanDataReset[0] = 0;
    //gaugeCanData[1] = 0;
    socketCanWriter.send(gaugeCanDataReset, 1, 0x321);

    // int iconsCanDataReset[2];
    // iconsCanDataReset[0] = 0x00;
    // iconsCanDataReset[1] = 0x00;
    // // iconsCanDataReset[2] = 0x00;
    // socketCanWriter.send(gaugeCanDataReset, 2, 0x213);

    // int userinCanDataReset[2];
    // userinCanDataReset[0] = 0x00;
    // userinCanDataReset[1] = 0x00;
    // socketCanWriter.send(userinCanDataReset, 2, 0x111);

}

void Emulator::clusterCheck() {
    int iconsData[2];
    
    if (isChecked == false) {
        iconsData[0] = 0x00;
        iconsData[1] = 0x00;
        socketCanWriter.send(iconsData, 2, 0x213);
        checkCnt++;
    }
    if (checkCnt == 200) {
        iconsData[0] = 0;
        iconsData[1] = 0;
        socketCanWriter.send(iconsData, 2, 0x213);
        isChecked = true;
        checkCnt = 0;
    }
}

float Emulator::calculateTorque(){
    float maxEngineTorque;
    if (engineRPM <= 2020){
        maxEngineTorque = 0.0755 *engineRPM + 228,5;
    }else if(engineRPM > 2020 && engineRPM <= 2990){
        maxEngineTorque = 0.0557 *engineRPM + 272,5;
    }else if(engineRPM > 2990 && engineRPM <= 3500){
        maxEngineTorque = 0.0216 *engineRPM + 374,4;
    }else if(engineRPM > 3500 && engineRPM <= 5000){
        maxEngineTorque =  450;
    }else if(engineRPM > 5000 && engineRPM <= 6000) {//6500){
        maxEngineTorque = (-0.0553 * engineRPM) + 726,5;
    } else if(engineRPM > 6000){
        maxEngineTorque = 25;
    }
    
    if (brkPedal > 0) {
        return 0;
    } else {
        return maxEngineTorque * gasPedalPosition / 100;
    }
}

float Emulator::tractionForce(){
    if(gearPosition == D || gearPosition == R){

        return calculateTorque() * gearRatios[gearIndex] *finalDriveRatio * drivelineEfficiency / dynamicWheelRadius;
    } else {
        return 0;
    }
    
}

float Emulator::aerodynamicForce(){
    return airDensity * dragCoefficient * vehicleFrontalArea * vehicleSpeed * vehicleSpeed / 2;
}

float Emulator::vehicleAcceleration() {
    float force = tractionForce();
    float brkForce = 0;
    if (gasPedalPosition == 0) {
        brkForce = engineBreakForce;
    }

    if (brkPedal == 1) {
        brkForce = engineBreakForce + 5000;
    }

    float sumForce = force - roadLoadForce - aerodynamicForce() - brkForce;
    if (vehicleSpeed == 0) {
        sumForce = force;
    }
    if ((gasPedalPosition == 0) && ((engineRPM < 1050) && (engineRPM > 950))) {
        sumForce = 0;
    }

    if(gearPosition == R){
        sumForce = - sumForce;
    }

    return  sumForce / vehicleMass;
}

void Emulator::setVehicleSpeed(){
    float lastVehicleSpeed = vehicleSpeed;
    float dV = dT * vehicleAcceleration();
    vehicleAcc = vehicleAcceleration();
    vehicleSpeed += dV;
    if(lastVehicleSpeed * vehicleSpeed < 0){
        vehicleSpeed = 0;
    }
}

void Emulator::shiftScheduler(){
    if(gearPosition == D){
        if (engineRPM >= 5000 && gearIndex < 7){
            gearIndex = gearIndex +1;
        } else if (engineRPM <= 3000 && gearIndex > 0){
            gearIndex = gearIndex - 1;
        }
    } else if(gearPosition == R){
        gearIndex = 0;
    }
}

float Emulator::engineRPMChangeInNeutral(){
    float engineRPMChange;
    if(gasPedalPosition == 0){
        engineRPMChange = - 8 * neutralRatio;
    } else{
        if (engineRPM <= 2020){
            engineRPMChange = 20.4 * neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 2020 && engineRPM <= 2990){
            engineRPMChange = 23.8 * neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 2990 && engineRPM <= 3500){
            engineRPMChange = 26.1 * neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 3500 && engineRPM <= 5000){
            engineRPMChange = 26.4 * neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 5000) {//6500){
            engineRPMChange = 24.1 * neutralRatio * gasPedalPosition / 100;
        }
    }
    return engineRPMChange;
}

void Emulator::calculateEngineRPM(){
    if(gearPosition == D || gearPosition == R){
        this->engineRPM = 30 * absolute(vehicleSpeed) / dynamicWheelRadius * gearRatios[gearIndex] *finalDriveRatio / 3.14;
    } else {
        this->engineRPM += engineRPMChangeInNeutral();
    }
    if(engineRPM < engineIdlingRPM - 200){
        this->engineRPM = engineIdlingRPM;
    }else if(engineRPM > engineMaxRPM){
        this->engineRPM = engineMaxRPM - 750;
    }
}

void Emulator::run() {
    const std::lock_guard<std::mutex> lock(mu);
    calculateTorque();
    setVehicleSpeed();
    calculateEngineRPM();
    shiftScheduler();
}

void Emulator::print() {
    const std::lock_guard<std::mutex> lock(mu);
    std::cout << "Ignition: " << isIgnitionOn << ", acc%: " << gasPedalPosition << ", brk: " << brkPedal << ", Acceleration: " << vehicleAcc <<  ", gear index: " << gearIndex << ", engine RPM: " << engineRPM << ", vehicle speed: " <<vehicleSpeed << std::endl;
}

bool Emulator::terminator() {
    return isTerminated;
}