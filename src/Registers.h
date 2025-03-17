#ifndef REGISTERS_H
#define REGISTERS_H

#include <stdint.h>

extern uint8_t A; // Accumulator register
extern uint8_t X; // Index register
extern uint8_t Y; // Index register
extern uint8_t P; // State register
extern uint8_t SP; // Stack pointer
extern uint16_t PC; // Program counter

#endif
