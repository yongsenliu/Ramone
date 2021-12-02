#ifndef VEHICLEPARAMETERS_HPP
#define VEHICLEPARAMETERS_HPP

namespace VE {
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
        const float spdConvert = 2.23694;// parameter for converting m/s to mile/s
        const int fakeGaugeData1 = 100;
        const int fakeGaugeData2 = 200;
        const int fakeGaugeData3 = 50;
        const int maxEngineIgnitionOffSpeed = 10; //[m/s]

        //Road:
        const float roadLoadForce = 205.892; // total road load force (resistance due to slope, friction) [Nm]
        
        //Engine constants:
        const int tqFullLoad[6] = {306, 385, 439, 450, 450, 367}; // engine torque curve at full load [Nm]
        const int NtqFullLoad[6] = {1000, 2020, 2990, 3500, 5000, 6500}; // engine speed axis [rpm]
        const float engineIdlingRPM = 1000; //[rpm]
        const float engineMaxRPM = 7000; //[rpm]
        const float engineBrakeForce = 1000.0; //[Nm]
        
        //Transmission constants:
        const float gearRatios[8] = {4.71, 3.14, 2.11, 1.67, 1.29, 1.00, 0.84, 0.67}; // gearbox gear ratios
        const float neutralRatio = 4.5;
        const int gearShiftPointLowRPM = 3000; //[rpm]
        const int gearShiftPointHighRPM = 5000; //[rpm]
        
        //Powertrain constants
        const float finalDriveRatio = 3.31; // final drive ratio (differential)
        const float drivelineEfficiency = 0.85; // driveline efficiency
        const int defaultBrakePedalForce = 7000; //[Nm]
        
        //Simulation constants:
        const float dT = 0.01; // sample time [s] 
        const int egineCanID = 0x123;
        const int gearboxCanID = 0x312;
        const int gaugeCanID = 0x321;
    
}

#endif