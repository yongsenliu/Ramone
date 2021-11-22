#ifndef CLUSTERUPDATE_H
#define CLUSTERUPDATE_H
#include <QtCore/QObject>
#include <QtCore/QVariant>

struct _icons {
    unsigned short hazard : 1;
    unsigned short right_blinker : 1;
    unsigned short left_blinker : 1;
    unsigned short engine_check : 1;
    unsigned short oil_check : 1;
    unsigned short abs : 1;
    unsigned short battery : 1;
    unsigned short seat_belt : 1;
    unsigned short doors_open : 1;
    unsigned short high_beam : 1;
    unsigned short hand_break : 1;
    unsigned short _reserved_pad : 5;
}__attribute__((packed));

class ClusterUpdater/* : public QObject*/ {
//    Q_OBJECT
public:
    ClusterUpdater() = default;
    inline void init(QObject*_){this->ValueSource=_;}


public:
    void setIcon(const _icons *_i);

    /** RPM value 0 - 9000 **/
    inline void setRPM(const double &_s) {ValueSource->setProperty("rpmHezar",QVariant(_s));}
    /** Speed betwwen 0 - 250 **/
    inline void setSpeed(const double &_s) {ValueSource->setProperty("kph",QVariant(_s));}
    /** GearNumber **/
    inline void setGear(const char &_s) {ValueSource->setProperty("gear",QVariant(_s));}
    /** 0=P, 1=N, 2=R, 3=D, 4=M **/
    inline void setGearPindle_int(const char &_p)  {ValueSource->setProperty("pindle_int",QVariant(_p));}
    /** Set a char directly to gear Pindle Position **/
    inline void setGearPindle_char(const char &_p) {ValueSource->setProperty("prindle",QVariant(_p));}

    /** Gauges receive a value between 0(MIN) and 255(MAX) **/
    inline void setFuelGauges(const double &_f) {ValueSource->setProperty("fuel",QVariant(_f/0xFF));}
    inline void setTemperatureGauges(const double &_t) {ValueSource->setProperty("temperature",QVariant(_t/0xFF));}
    inline void setOilTemperatureGauges(const double &_t) {ValueSource->setProperty("oil_temp",QVariant(_t/0xFF));}

    /** 0: off 1: on **/
    inline void ignite(const int &_t) {ValueSource->setProperty("startUp",QVariant(_t));}
    /** Set Text on the Screen **/
    inline void setTXT(const QString &_s) {ValueSource->setProperty("txt",QVariant(_s));}

private:
    QObject *ValueSource;
    void checkHazard(const _icons *_i);
    unsigned short iconZ;
};

#endif // CLUSTERUPDATE_H
