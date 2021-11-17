#ifndef TRANS_HPP
#define TRANS_HPP

class Trans {
/*Constants*/
    const int gearMin = 1; // lowest gear
    const int gearMax = 8; // highest gear
    const float gearRat[8] = {4.71, 3.14, 2.11, 1.67, 1.29, 1.00, 0.84, 0.67}; // gearbox gear ratios
    const float i0 = 3.31; // final drive ratio (differential)
    const float eff = 0.85; // driveline efficiency
public:
    void test();  
    int shiftScheduler(int engRPM);
};

#endif