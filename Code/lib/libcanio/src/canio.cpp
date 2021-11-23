#include <iostream>
#include <cstring>
#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include "canio.h"

namespace CAN_GENERIC {
bool setSocketNONBlockingEnabled(const int &_fd, const bool &_blocking = false) {
   if (_fd < 0) return false;
   int flags = fcntl(_fd, F_GETFL, 0);
   flags = _blocking ? (flags & ~O_NONBLOCK) : (flags | O_NONBLOCK);
   return (fcntl(_fd, F_SETFL, flags) == 0) ? true : false;
}
void printErr(const char *_errMSG) {
    std::cerr << "[!!!] " << _errMSG << std::endl;
    std::cerr << "[!!!] Error Number " << errno << ": " << strerror(errno) << std::endl;
}
} // namespace CAN_GENERIC

bool CANio::open(const std::string &_ifname) {
    struct ifreq ifr;
    struct sockaddr_can addr;
    if ((fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        CAN_GENERIC::printErr("Cannot open CAN!");
        return false;
    }

    std::strncpy(ifr.ifr_name, _ifname.c_str(), IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = 0x00;
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (!ifr.ifr_ifindex) {
        CAN_GENERIC::printErr(_ifname.c_str());
        return false;
    }

    if (!CAN_GENERIC::setSocketNONBlockingEnabled(fd)) {
        CAN_GENERIC::printErr("Cannot set socket non blocking!");
        return false;
    }

    int optval = 7;
    setsockopt(fd, SOL_SOCKET, SO_PRIORITY, &optval, sizeof(optval));

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        CAN_GENERIC::printErr("Cannot Bind!");
        return false;
    }
    return true;
}

bool CANio::write(const uint32_t &_id, const size_t &_len, const uint8_t * const _data) {
    struct canfd_frame frame;
    std::memset(&frame, 0, sizeof(frame));
    frame.can_id = _id;
    std::memcpy(frame.data, _data, _len);
    frame.len = _len;
    return this->write(&frame);
}

bool CANio::write(const canfd_frame * const frame) {
    bool ret = false;    
    if (::write(fd, frame, int(CAN_MTU)) != int(CAN_MTU))
        CAN_GENERIC::printErr("Write Error!");
    else ret = true;
    return ret;
}

READ_STATUS CANio::read(canfd_frame *frame) {
    READ_STATUS ret = READ_STATUS::ERROR;
    auto num_bytes = ::read(fd, frame, CAN_MTU);
    if (num_bytes == 0) ret = READ_STATUS::ENDOF;
    else if ((num_bytes == -1) && errno==11) ret = READ_STATUS::NOT_AVAILABLE;
    else if (num_bytes != CAN_MTU) CAN_GENERIC::printErr("Read Error!");
    else ret = READ_STATUS::OK;
    return ret;
}

CANio::~CANio() {
    ::close(fd);
}




