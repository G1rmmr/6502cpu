#ifndef FLAGS_H
#define FLAGS_H

#include <stdint.h>

extern enum {
    C = 0x01, // Carry
    Z = 0x02, // Zero
    I = 0x04, // Interrupt Disable
    D = 0x08, // Decimal
    B = 0x10, // Break
    U = 0x20, // Unused
    V = 0x40, // Overflow
    N = 0x80  // Negative
} Flags;

extern void SetFlag(uint8_t flag, int condition);
extern void SetZNFlags(uint8_t value);

#endif
