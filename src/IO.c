#include "IO.h"

#include <stdio.h>

#include "Memory.h"

void HandleIOWrite(uint16_t addr, uint8_t value) {
    switch (addr) {
    case IO_OUTPUT_BUF:
        putchar(value);
        fflush(stdout);
        break;

    case IO_OUTPUT_FLAG:
        break;

    default:
        RAM[addr] = value;
        break;
    }
}

void UpdateKeyboardInput() {
    int ch = getchar();
    if(ch != EOF) RAM[IO_KEYBOARD] = (uint8_t)ch;
}

void WriteMemory(uint16_t addr, uint8_t value) {
    if(addr == IO_KEYBOARD
    || addr == IO_OUTPUT_BUF
    || addr == IO_OUTPUT_FLAG)
        HandleIOWrite(addr, value);

    else if (addr >= ROM_START && addr <= ROM_END)
        printf("Attempt to write to ROM: 0x%04X\n", addr);

    else RAM[addr] = value;
}

uint8_t ReadMemory(uint16_t addr) {
    return RAM[(addr == IO_KEYBOARD) ? IO_KEYBOARD : addr];
}
