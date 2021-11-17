#ifndef EMU_HPP
#define EMU_HPP

class Emu {
// The God now, later will be split below properties and methods 
// into engine and trans class...
private:
/*Constants*/
// Tires
    const float tireW = 0.295; // tire width [m]
    const float tireD = 20 * 0.0254; // rim diameter [m]
    const float tireMiua = 1.1; // wheel (tire) friction coefficient
    const float tireLoad = 0.65; // rear axle load coeeficient
// Vehicle
    const int vehMass_curb = 1741; // [kg]
    const float vehMass_fm = 1.05; // mass factor
    const float g = 9.81; // gravitational acceleration [m/s2]
    const float vehCd = 0.36; // drag coefficient
    const float vehFa = 2.42; // frontal area [m2]
    const float vehRo = 1.202; // air density [kg/m3]
// Road
    float roadSlope = 0; // road slope angle [rad]
    const float roadCr = 0.011; // road load coefficient

/*Variables*/
    int rate;
    int currentEngineRpm;
    int currentAccPos;
    int lastAccPos;
public:
    Emu() = default;
    int currentTime;
    int lastTick;
    void setAccPedalPos(int inputAcc);
    int getAccPedalPos();

    int getRpm();
    void updateRpm(int acc);
    void outputRpm(int rpm);
    // more to be added 
};
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    
#endif