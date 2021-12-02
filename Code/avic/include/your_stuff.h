#ifndef YOUR_STUFF_H
#define YOUR_STUFF_H
#include "can_opener.h"
#include "cluster_updater.h"

class yourStuff : public QObject {
    Q_OBJECT
public:
    yourStuff() = delete;
    yourStuff(const std::string &_ifName, QObject *_);

private:
    bool run();
    void YouHaveJustRecievedACANFrame(const canfd_frame * const _frame);    
    void timerEvent(QTimerEvent*) override;

//signals:
//    void die();

private:
    size_t Counter = 0;
    CANOpener CANReader;
    ClusterUpdater InstrumentCluster;

};

#endif // YOUR_STUFF_H
