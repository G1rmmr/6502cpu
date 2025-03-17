#ifndef IO_H
#define IO_H

#define IO_KEYBOARD 0x8000
#define IO_OUTPUT_BUF 0x8001
#define IO_OUTPUT_FLAG 0x8002

#define ROM_START 0x8000
#define ROM_END 0xFFFF

#include <stdint.h>

extern void HandleIOWrite(uint16_t addr, uint8_t value);
extern void UpdateKeyboardInput();

extern void WriteMemory(uint16_t addr, uint8_t value);
extern uint8_t ReadMemory(uint16_t addr);

#endif
