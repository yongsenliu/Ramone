#ifndef CANBUFFER_HPP
#define CANBUFFER_HPP

#include <mutex>

typedef union _bufferData
{
    struct  _attribute_((packed)) _inner {
        uint16_t id;
        unsigned char length;
        unsigned char data[8]
    }inner;
    unsigned char Data[11];
    
}CanBufferData;

class CanBuffer
{
private:
    bool empty = true;
    mutable std::mutex mu;
public:
    CanBuffer(/* args */) = default;
    void push(const u_int16_t &id, const unsigned char &length, unsigned char data[]);
    auto pull();
    bool isEmpty();
    ~CanBuffer();
};

#endif