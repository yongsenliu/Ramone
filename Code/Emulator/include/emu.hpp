#ifndef EMU_HPP
#define EMU_HPP

class Emu {
// The God now, later will be split below properties and methods 
// into engine and trans class...
private:
    int currentTime;
    int lastTick;
    int rate;
    int currentEngineRpm;
    int currentAccPos;
public:
    int getAccPedalPos();
    void updateRpm(int acc);
    void outputRpm(int rpm);
    // more to be added 
}

#endif
