#ifndef MONITOR_H
#define MONITOR_H

#include <stdint.h>

extern void PrintRegisters();
extern void DumpMemory(const uint16_t start, const uint16_t end);

#endif
