#ifndef CANIO_H
#define CANIO_H
#include <cstdint>
#include <string>
#include <linux/can.h>
enum READ_STATUS {
    OK,
    ENDOF,
    NOT_AVAILABLE,
    ERROR
};
class CANio {
public:
    CANio() = default;
    CANio(const CANio &) = delete;
    CANio & operator=(const CANio &) = delete;
    bool open(const std::string &can_interface);
    bool write(const uint32_t &_id,
               const size_t &_len,
               const uint8_t * const _data);
    bool write(const struct canfd_frame * const frame);
    READ_STATUS read(canfd_frame *frame);
    ~CANio();
private:
    int fd = -1;


















};
#endif // CANIO_H
