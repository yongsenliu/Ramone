#include <iostream>
#include <unistd.h>
#include <cstring>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <linux/can/raw.h>
#include <fcntl.h>
#include "can_opener.h"

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


bool CANOpener::open(const std::string &_ifName) {
    struct ifreq ifr;
    struct sockaddr_can addr;

    if ((fd = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        CAN_GENERIC::printErr("Cannot open CAN!");
        return false;
    }

    strncpy(ifr.ifr_name, _ifName.c_str(), IFNAMSIZ - 1);
    ifr.ifr_name[IFNAMSIZ - 1] = 0x00;
    ifr.ifr_ifindex = if_nametoindex(ifr.ifr_name);
    if (!ifr.ifr_ifindex) {
        CAN_GENERIC::printErr( _ifName.c_str());
        return false;
    }

    if (!CAN_GENERIC::setSocketNONBlockingEnabled(fd)) {
        CAN_GENERIC::printErr("Cannot set socket non blocking!");
        return false;
    }

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;
    if (bind(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        CAN_GENERIC::printErr("Cannot Bind!");
        return false;
    }

    return true;
}

CANOpener::ReadStatus CANOpener::read(struct canfd_frame *_frame) {
    CANOpener::ReadStatus ret = ReadStatus::OK;
    auto num_bytes = ::read(fd, _frame, CAN_MTU);
    if (num_bytes == 0) ret = ReadStatus::ENDOF;
    else if ( (num_bytes == -1) && (errno==11) ) ret = ReadStatus::NAVAL;
    else if (num_bytes != CAN_MTU) {
        CAN_GENERIC::printErr("Cannot Read!");
        ret = ReadStatus::ERROR;
    }
    return ret;
}

CANOpener::~CANOpener() {
    ::close(fd);
}
