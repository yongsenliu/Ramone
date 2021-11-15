#ifndef EMU_HPP
#define EMU_HPP

class Emu {
// The God now, later will be split below properties and methods 
// into engine and trans class...
private:
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