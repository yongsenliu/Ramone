#ifndef Emulator_H
#define Emulator_H
#define MAX_SPD 120

enum gearPosition_t {P,D,N,R};

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
        
	    void outputRpm(int rpm);
        
        void canReader();

    private:
        int gaspedalPosition = 0;
        int engineRPM = 0;
        int carWeight = 0;
        int carDrivingTime = 0;
        gearPosition_t gearPosition = N;
};

#endif // Emulator_H
