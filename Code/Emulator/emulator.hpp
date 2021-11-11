#ifndef Emulator_H
#define Emulator_H
class Emulator{

    public:
        Emulator()= default;
        Emulator(const int carWeight);

        enum gearPosition_t {N,D,R,P};

        bool setgearPosition(gearPosition_t currentGearPos);
        gearPosition_t getGearPosition();

        bool setGaspedalPostion (int gaspdedalPos);
        int getGaspedalPositon();

        int getEngineRPM();
        bool setEngineRPM(int engineRPM);

    private:
        int gaspedalPosition = 0;
        int engineRPM = 0;
        int carWeight = 0;
        int carDrivingTime = 0;
        gearPosition_t gearPosition = N;
};

#endif // Emulator_H