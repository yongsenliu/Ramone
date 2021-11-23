#ifndef CAN_CMN_H
#define CAN_CMN_H
#include <cstdint>
namespace CAN {
namespace MSG {

static const uint32_t ENGINE_ID = 0x123;
static const uint32_t GEARBX_ID = 0x312;
static const uint32_t ICONSS_ID = 0x213;
static const uint32_t GAUGES_ID = 0x321;

static const uint32_t USERIN_ID = 0x111;
static const uint32_t TESTTT_ID = 0x222;











namespace MASK {

static const uint16_t HZRD = 0b10000000000;
static const uint16_t ICN0 = 0b01000000000;
static const uint16_t ICN1 = 0b00100000000;
static const uint16_t ICN2 = 0b00010000000;
static const uint16_t ICN3 = 0b00001000000;
static const uint16_t ICN4 = 0b00000100000;
static const uint16_t ICN5 = 0b00000010000;
static const uint16_t ICN6 = 0b00000001000;
static const uint16_t ICN7 = 0b00000000100;
static const uint16_t ICN8 = 0b00000000010;
static const uint16_t ICN9 = 0b00000000001;
}



typedef union _icons{
    struct __attribute__((packed)) _bits{
    unsigned char HZRD:1;
    unsigned char ICN0:1;
    unsigned char ICN1:1;
    unsigned char ICN2:1;
    unsigned char ICN3:1;
    unsigned char ICN4:1;
    unsigned char ICN5:1;
    unsigned char ICN6:1;
    //
    unsigned char ICN7:1;
    unsigned char ICN8:1;
    unsigned char ICN9:1;
    unsigned char RESERVERD_PADDING:5;
    }Bits;
    uint8_t Data[2];
}Iconss_t;

typedef union _gearbox{
    struct  _bits {
    unsigned char GEAR_P:3;
    unsigned char GEAR_N:3;
    unsigned char RESERVERD_PADDING:2;
    }Bits;
    uint8_t Data[2];
}Gearbx_t;

typedef struct _userin{
    unsigned char ACCL:1;
    unsigned char BREK:1;
    unsigned char IGNT:1;
    unsigned char GRDN:1;
    unsigned char GRUP:1;
    unsigned char GRLF:1;
    unsigned char GRRT:1;
    unsigned char RESERVERD_PADDING:1;
}UserIn_t;

typedef struct _engine {
    unsigned short RPM;
    unsigned short SPD;
    unsigned short RUN;
}Engine_t;

typedef union _gauge{
    struct __attribute__((packed)) _inner{
    unsigned char G_FUEL;
    unsigned char G_OILT;
    unsigned char G_TEMP;
    }Inner;
    uint8_t Data[3];
}Gauges_t;

void printGauges(const Gauges_t::_inner *_g);
void printIconss(const Iconss_t::_bits *_i);
void printGearbx(const Gearbx_t &_g);
void printEngine(const Engine_t &_e);
void printUserIn(const UserIn_t *_u);

} // namespace MSG
} // namespace CAN
#endif // CAN_CMN_H












