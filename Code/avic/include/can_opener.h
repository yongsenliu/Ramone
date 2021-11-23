#ifndef CANOPENER_H
#define CANOPENER_H
#include <cstdint>
#include <string>
#include <linux/can.h>

class CANOpener {
public:
    enum class ReadStatus {
        OK,
        ENDOF,
        ERROR,
        NAVAL,
    };
    CANOpener() = default;
    ~CANOpener();
    CANOpener(const CANOpener &) = delete;
    CANOpener & operator=(const CANOpener &) = delete;
    bool open(const std::string &_ifName);
    ReadStatus read(struct canfd_frame *_frame);

private:
    int fd = -1;
};



#endif // CANOPENER_H
