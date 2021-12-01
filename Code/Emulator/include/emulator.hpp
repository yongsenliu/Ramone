#ifndef Emulator_H
#define Emulator_H

#include <iostream>
#include <cmath>
#include <thread>
#include <mutex>
#include <thread>
#include <bitset>
#include <chrono>
#include "../../libSocketCan/include/socketcan.hpp"
#include "VehicleParameters.hpp"

enum class gearPosition_t {P,D,N,R};

enum class ignition_t {OFF, ON};

typedef union _gearbox{
    struct  _bits {
    unsigned char GEAR_P:3;
    unsigned char GEAR_N:3;
    unsigned char RESERVERD_PADDING:2;
    }Bits;
    uint8_t Data[1];
}Gearbx_t;

typedef struct _engine
{
    unsigned char accPedalPos;
    unsigned char gearboxPos;
    unsigned char ignition;
    unsigned char brkPedalPos;
    unsigned char isTerminated;
}Engine_t;

class Emulator{
    public:
        Emulator();
        void canReader();
        void canSender();
        void canSender_reset();
        void clusterCheck();
        void setIgnition();
        bool ignitionOn();
        int rasterTimeInMiliSeconds();
        float calculateTorque();
        float tractionForce();
        float aerodynamicForce();
        float vehicleAcceleration();
        void setVehicleSpeed();
        void shiftScheduler();
        void calculateEngineRPM();
        float engineRPMChangeInNeutral();
        void run();
        void print();
        bool terminator();

    private:
    /*Variables*/
        int gasPedalPosition = 0;
        float engineRPM = VE::engineIdlingRPM;
        gearPosition_t gearPosition = gearPosition_t::N;
        ignition_t ignition = ignition_t::OFF;
        mutable std::mutex mu;
        int gearIndex = 0;
        float vehicleSpeed = 0;
        float vehicleAcc = 0;
        int brkPedal = 0;
        bool isIgnitionOn = false;
        int checkCnt = 0;

        bool isTerminated = false;

    /*CAN communication*/
        scpp::SocketCan socketCanReader;
        scpp::SocketCan socketCanWriter;
    };

#endif // Emulator_H
