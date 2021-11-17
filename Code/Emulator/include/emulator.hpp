#ifndef Emulator_H
#define Emulator_H
#define MAX_SPD 5000
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

        bool ignitionOn();

    private:

        int gasPedalPosition = 0;
        int lastAccPos = 0;
        float engineRPM = 0.0;
        int carWeight = 0;
        int carDrivingTime = 0;
        gearPosition_t gearPosition = N;
        ignition_t ignition = ON;
        std::mutex mu;
};

#endif // Emulator_H
