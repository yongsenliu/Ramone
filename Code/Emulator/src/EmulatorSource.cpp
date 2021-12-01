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
    if ((brkPedal > 0) && (ignition == ignition_t::ON)) {
        isIgnitionOn = true;
    }

    if ((vehicleSpeed < VE::maxEngineIgnitionOffSpeed) && (ignition == ignition_t::OFF)) {
        isIgnitionOn = false;
    }

}

bool Emulator::ignitionOn() {
    return isIgnitionOn;
}

int Emulator::rasterTimeInMiliSeconds(){
    return VE::dT * 1000;
}

void Emulator::canReader(){
    while (!terminator()) {
        scpp::CanFrame fr;
        if (socketCanReader.read(fr) == scpp::STATUS_OK) {
            printf("len %d byte, id: %d, data: %02x %02x %02x %02x %02x \n", fr.len, fr.id, 
                fr.data[0], fr.data[1], fr.data[2], fr.data[3], fr.data[4]);

            std::lock_guard<std::mutex> lock(mu);



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
    
    engineCanData[0] = int(engineRPM) % 256;
    engineCanData[1] = int(engineRPM) / 256;
    
    engineCanData[2] = int(fabs(vehicleSpeed) * VE::spdConvert) % 256;
    engineCanData[3] = int(fabs(vehicleSpeed) * VE::spdConvert) / 256;

    engineCanData[4] = 0xff;
    engineCanData[5] = 0xff;
    socketCanWriter.send(engineCanData, 6, VE::egineCanID);

    int gearboxCanData[2];
    Gearbx_t g;

    if (gearPosition == gearPosition_t::P) {
        g.Bits.GEAR_P = 0; //0b000
    } else if (gearPosition == gearPosition_t::N) {
        g.Bits.GEAR_P = 1; //0b001
    } else if (gearPosition == gearPosition_t::D) {
        g.Bits.GEAR_P = 3; //0b011
    } else if (gearPosition == gearPosition_t::R) {
        g.Bits.GEAR_P = 2; //0b010
    }

    g.Bits.GEAR_N = gearIndex;
    
    gearboxCanData[0] = g.Data[0];
    gearboxCanData[1] = g.Data[1];

    socketCanWriter.send(gearboxCanData, 2, VE::gearboxCanID);

    int gaugeCanData[3];
    gaugeCanData[0] = VE::fakeGaugeData1;
    gaugeCanData[1] = VE::fakeGaugeData2;
    gaugeCanData[2] = VE::fakeGaugeData3;

    socketCanWriter.send(gaugeCanData, 3, VE::gaugeCanID);


}

void Emulator::canSender_reset() {
    int engineCanDataReset[5];
    engineCanDataReset[0] = 0;
    engineCanDataReset[1] = 0;
    engineCanDataReset[2] = 0;
    engineCanDataReset[3] = 0;
    socketCanWriter.send(engineCanDataReset, 4, VE::egineCanID);
    
    int gearboxCanDataReset[2];
    gearboxCanDataReset[0] = 0x00;
    gearboxCanDataReset[1] = 0x00;
    socketCanWriter.send(gearboxCanDataReset, 2, VE::gearboxCanID);

    int gaugeCanDataReset[1];
    gaugeCanDataReset[0] = 0;
    //gaugeCanData[1] = 0;
    socketCanWriter.send(gaugeCanDataReset, 1, VE::gaugeCanID);

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

float Emulator::calculateTorque(){
    float maxEngineTorque;
    if (engineRPM <= 2020){
        maxEngineTorque = 0.0755 *engineRPM + 228.5;
    }else if(engineRPM > 2020 && engineRPM <= 2990){
        maxEngineTorque = 0.0557 *engineRPM + 272.5;
    }else if(engineRPM > 2990 && engineRPM <= 3500){
        maxEngineTorque = 0.0216 *engineRPM + 374.4;
    }else if(engineRPM > 3500 && engineRPM <= 5000){
        maxEngineTorque =  450;
    }else if(engineRPM > 5000 && engineRPM <= 6000) {
        maxEngineTorque = (-0.0553 * engineRPM) + 726.5;
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
    // if(gearPosition == D || gearPosition == R){

    //     return calculateTorque() * gearRatios[gearIndex] *finalDriveRatio * drivelineEfficiency / dynamicWheelRadius;
    
    // } else {
    //     return 0;
    // }

    if (gearPosition == gearPosition_t::D) {
        return calculateTorque() * VE::gearRatios[gearIndex] *VE::finalDriveRatio * VE::drivelineEfficiency / VE::dynamicWheelRadius;
    } else if (gearPosition == gearPosition_t::R) {
        return - calculateTorque() * VE::gearRatios[gearIndex] *VE::finalDriveRatio * VE::drivelineEfficiency / VE::dynamicWheelRadius;
    } else {
        return 0;
    }
}

float Emulator::aerodynamicForce(){
    return VE::airDensity * VE::dragCoefficient * VE::vehicleFrontalArea * vehicleSpeed * vehicleSpeed / 2;
}

float Emulator::vehicleAcceleration() {
    float force = tractionForce();
    float brkForce = 0;
    float sumForce = 0;
    if (gasPedalPosition == 0) {
        brkForce = VE::engineBrakeForce;
    }

    if (brkPedal == 1) {
        brkForce = VE::engineBrakeForce + VE::defaultBrakePedalForce;
    }

    if (vehicleSpeed == 0) {
        sumForce = force;
    } else if (vehicleSpeed < 0) {
        sumForce = force + VE::roadLoadForce + aerodynamicForce() + brkForce;
    } else if (vehicleSpeed > 0) {
        sumForce = force - VE::roadLoadForce - aerodynamicForce() - brkForce;
    }

    if ((gasPedalPosition == 0) && ((engineRPM < (VE::engineIdlingRPM + 50)) && (engineRPM > (VE::engineIdlingRPM - 50)))) {
        sumForce = 0;
    }

    // if(gearPosition == R){
    //     sumForce = - sumForce;
    // }

    return  sumForce / VE::vehicleMass;
}

void Emulator::setVehicleSpeed(){
    float lastVehicleSpeed = vehicleSpeed;
    float dV = VE::dT * vehicleAcceleration();
    vehicleAcc = vehicleAcceleration();
    vehicleSpeed += dV;
    if(lastVehicleSpeed * vehicleSpeed < 0){
        vehicleSpeed = 0;
    }
}

void Emulator::shiftScheduler(){
    if(gearPosition == gearPosition_t::D){
        if (engineRPM >= VE::gearShiftPointHighRPM && gearIndex < 7){
            gearIndex = gearIndex +1;
        } else if (engineRPM <= VE::gearShiftPointLowRPM && gearIndex > 0){
            gearIndex = gearIndex - 1;
        }
    } else if(gearPosition == gearPosition_t::R){
        gearIndex = 0;
    }
}

float Emulator::engineRPMChangeInNeutral(){
    float engineRPMChange;
    if(gasPedalPosition == 0){
        engineRPMChange = - 8 * VE::neutralRatio;
    } else{
        if (engineRPM <= 2020){
            engineRPMChange = 20.4 * VE::neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 2020 && engineRPM <= 2990){
            engineRPMChange = 23.8 * VE::neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 2990 && engineRPM <= 3500){
            engineRPMChange = 26.1 * VE::neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 3500 && engineRPM <= 5000){
            engineRPMChange = 26.4 * VE::neutralRatio * gasPedalPosition / 100;
        }else if(engineRPM > 5000) {//6500){
            engineRPMChange = 24.1 * VE::neutralRatio * gasPedalPosition / 100;
        }
    }
    return engineRPMChange;
}

void Emulator::calculateEngineRPM(){
    if(gearPosition == gearPosition_t::D || gearPosition == gearPosition_t::R){
        this->engineRPM = 30 * fabs(vehicleSpeed) / VE::dynamicWheelRadius * VE::gearRatios[gearIndex] *VE::finalDriveRatio / 3.14;
    } else {
        this->engineRPM += engineRPMChangeInNeutral();
    }
    if(engineRPM < VE::engineIdlingRPM - 200){
        this->engineRPM = VE::engineIdlingRPM;
    }else if(engineRPM > VE::engineMaxRPM){
        this->engineRPM = VE::engineMaxRPM - 750;
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
    std::cout << "Terminated?: " << isTerminated << ", Ignition: " << isIgnitionOn << ", acc%: " << gasPedalPosition << ", brk: " << brkPedal << ", Acceleration: " << vehicleAcc <<  ", gear index: " << gearIndex << ", engine RPM: " << engineRPM << ", vehicle speed: " <<vehicleSpeed << std::endl;
}

bool Emulator::terminator() {
    return isTerminated;
}