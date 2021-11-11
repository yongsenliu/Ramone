#ifndef EMU_HPP
#define EMU_HPP

class Emu {
private:
    int lastTick;
    int rate;
    int currentEngineRpm;
    int currentAccPos;
public:
    int getAccPedalPos();
    int calRpm(int acc);
    void outputRpm(int rpm);
}

#endif
