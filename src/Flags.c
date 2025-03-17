#include "Flags.h"
#include "Registers.h"

void SetFlag(uint8_t flag, int condition) {
    if(condition) P |= flag;
    else P &= ~flag;
}

void SetZNFlags(uint8_t value) {
    SetFlag(Z, value == 0);
    SetFlag(N, value & 0x80);
}
