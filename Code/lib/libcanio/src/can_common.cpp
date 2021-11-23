#include <iostream>
#include "can_common.h"
namespace CAN {
namespace MSG {
void printGauges(const Gauges_t::_inner *_g) {
    std::cout <<"G_FUEL: " << static_cast<unsigned>(_g->G_FUEL) << std::endl;
    std::cout <<"G_OILT: " << static_cast<unsigned>(_g->G_OILT) << std::endl;
    std::cout <<"G_TEMP: " << static_cast<unsigned>(_g->G_TEMP) << std::endl;
}

void printIconss(const Iconss_t::_bits *_i) {
    std::cout <<"HZRD: " << static_cast<unsigned>(_i->HZRD) << std::endl;
    std::cout <<"ICN0: " << static_cast<unsigned>(_i->ICN0) << std::endl;
    std::cout <<"ICN1: " << static_cast<unsigned>(_i->ICN1) << std::endl;
    std::cout <<"ICN2: " << static_cast<unsigned>(_i->ICN2) << std::endl;
    std::cout <<"ICN3: " << static_cast<unsigned>(_i->ICN3) << std::endl;
    std::cout <<"ICN4: " << static_cast<unsigned>(_i->ICN4) << std::endl;
    std::cout <<"ICN5: " << static_cast<unsigned>(_i->ICN5) << std::endl;
    std::cout <<"ICN6: " << static_cast<unsigned>(_i->ICN6) << std::endl;
    std::cout <<"ICN7: " << static_cast<unsigned>(_i->ICN7) << std::endl;
    std::cout <<"ICN8: " << static_cast<unsigned>(_i->ICN8) << std::endl;
    std::cout <<"ICN9: " << static_cast<unsigned>(_i->ICN9) << std::endl;
    std::cout <<"RESERVERD_PADDING: " <<
                static_cast<unsigned>(_i->RESERVERD_PADDING) << std::endl;
}

void printGearbx(const Gearbx_t &_g) {/*
    std::cout <<"GEAR_N: " << static_cast<unsigned>(_g.GEAR_N) << std::endl;
    std::cout <<"GEAR_P: " << static_cast<unsigned>(_g.GEAR_P) << std::endl;
    std::cout <<"RESERVERD_PADDING: " <<
                static_cast<unsigned> (_g.RESERVERD_PADDING) << std::endl;*/
}

void printEngine(const Engine_t &_e) {
    std::cout <<"RPM: " << static_cast<unsigned>(_e.RPM) << std::endl;
    std::cout <<"SPD: " << static_cast<unsigned>(_e.SPD) << std::endl;
}

void printUserIn(const UserIn_t *_u) {
    std::cout <<"IGNT: " << static_cast<unsigned>(_u->IGNT) << std::endl;

    std::cout <<"ACCL: " << static_cast<unsigned>(_u->ACCL) << std::endl;
    std::cout <<"BREK: " << static_cast<unsigned>(_u->BREK) << std::endl;
    std::cout <<"GRDN: " << static_cast<unsigned>(_u->GRDN) << std::endl;
    std::cout <<"GRUP: " << static_cast<unsigned>(_u->GRUP) << std::endl;
    std::cout <<"GRLF: " << static_cast<unsigned>(_u->GRLF) << std::endl;
    std::cout <<"GRRT: " << static_cast<unsigned>(_u->GRRT) << std::endl;
    std::cout <<"RESERVERD_PADDING: " <<
                static_cast<unsigned int>(_u->RESERVERD_PADDING) << std::endl;
}




} // namespace MSG
} // namespace CAN
#include "can_common.h"
