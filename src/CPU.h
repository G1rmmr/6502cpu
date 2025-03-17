#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#include "Instruction.h"

extern void InitCPU();
extern void RunCPU();

extern uint8_t Fetch();
extern Instruction* Decode(const uint8_t op);
extern void Execute(const Instruction* instr);

#endif
