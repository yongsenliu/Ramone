#ifndef Emulator_H
#define Emulator_H
#define MAX_SPD 7000 //FIXME: move to constants
#include <thread>
#include <mutex>


enum gearPosition_t {P,D,N,R};
enum ignition_t {OFF, ON};

class Emulator{

    public:
        Emulator()= default;
        Emulator(const int carWeight);

        bool setgearPosition(gearPosition_t currentGearPos);
        gearPosition_t getGearPosition();

        bool setGaspedalPostion (int gaspdedalPos);
        int getGaspedalPositon();

        int getEngineRPM();
        bool setEngineRPM(int engineRPM);
        
        void updateRpm();
	    void outputRpm();
        
        void canReader();
        void canSender();

        bool ignitionOn();

        void calculateTorque();
        float tractionForce();
        float aerodynamicForce();

        float vehicleAcceleration();
        void setVehicleSpeed();

        void shiftScheduler();

        void calculateEngineRPM();

        void run();

    private:
    /*Vehicle constants*/
        //Tires:
        const float tireW = 0.295; // tire width [m]
        const float tireD = 20 * 0.0254; // rim diameter [m]
        const float tireMiua = 1.1; // wheel (tire) friction coefficient
        const float tireLoad = 0.65; // rear axle load coeeficient
        const float dynamicWheelRadius = 0.33565;// dynamic wheel radius, calculated by 0.3425 *0.98 [m]
        //Vehicle:
        const int vehicleMass = 1908; // [kg]
        const float g = 9.81; // gravitational acceleration [m/s2]
        const float dragCoefficient = 0.36; // drag coefficient
        const float vehicleFrontalArea = 2.42; // frontal area [m2]
        const float airDensity = 1.202; // air density [kg/m3]
        
        //Road:
        //const float roadSlope = 0; // road slope angle [rad]
        //const float roadLoadCoe = 0.011; // road load coefficient
        const float roadLoadForce = 205.892; // total road load force (resistance due to slope, friction) [Nm]
        //Engine constants:
        //const int NmaxTq = 3500; // engine speed for maximum torque [rpm]
        //const int NmaxPwr = 6500; // engine speed for maximum power [rpm]
        const int tqFullLoad[6] = {306, 385, 439, 450, 450, 367}; // engine torque curve at full load [Nm]
        const int NtqFullLoad[6] = {1000, 2020, 2990, 3500, 5000, 6500}; // engine speed axis [rpm]
        const int Nmax = 6500; // maximum engine speed [rpm]
        const int Nmin = 1000; // minimum engine speed [rpm]
        //Transmission constants:
        const int gearMin = 1; // lowest gear
        const int gearMax = 8; // highest gear
        const float gearRatios[8] = {4.71, 3.14, 2.11, 1.67, 1.29, 1.00, 0.84, 0.67}; // gearbox gear ratios
        
        const float finalDriveRatio = 3.31; // final drive ratio (differential)
        const float drivelineEfficiency = 0.85; // driveline efficiency

        //Simulation constants:
        const float dT = 0.05; // sample time [s] 

    /*Variables*/
        int gasPedalPosition = 0;
        int lastAccPos = 0;
        float engineRPM = 0.0;
        int carDrivingTime = 0;
        gearPosition_t gearPosition = N;
        ignition_t ignition = ON;
        std::mutex mu;

        int gearIndex = 0;
        float engineTorque = 0;
        float vehicleSpeed = 0;
};

#endif // Emulator_H
