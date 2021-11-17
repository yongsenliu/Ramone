#ifndef ENGINE_HPP
#define ENGINE_HPP

class Engine {
/*Constants*/
    const int NmaxTq = 3500; // engine speed for maximum torque [rpm]
    const int NmaxPwr = 6500; // engine speed for maximum power [rpm]
    const int tqFullLoad[6] = {306, 385, 439, 450, 450, 367}; // engine torque curve at full load [Nm]
    const int NtqFullLoad[6] = {1000, 2020, 2990, 3500, 5000, 6500}; // engine speed axis [rpm]
    const int Nmax = 6500; // maximum engine speed [rpm]
    const int Nmin = 1000; // minimum engine speed [rpm]
/*Variables*/
    

public:
    void test();
    
};

#endif