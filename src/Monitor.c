#include "Monitor.h"

#include <stdio.h>

#include "Registers.h"
#include "Memory.h"

void PrintRegisters() {
    printf("A:  $%02X\tX:  $%02X\tY:  $%02X\n", A, X, Y);
    printf("SP: $%02X\tPC: $%04X\n", SP, PC);
    printf("P:  ");
    printf("[N=%d] [V=%d] [-=%d] [B=%d] [D=%d] [I=%d] [Z=%d] [C=%d]\n",
        !!(P & 0x80), !!(P & 0x40), !!(P & 0x20), !!(P & 0x10),
        !!(P & 0x08), !!(P & 0x04), !!(P & 0x02), !!(P & 0x01));
}

void DumpMemory(uint16_t start, uint16_t end) {
    for (uint16_t addr = start; addr <= end; addr += 16) {
        printf("%04X: ", addr);

        for (int i = 0; i < 16 && addr + i <= end; ++i)
            printf("%02X ", RAM[addr + i]);

        printf("\n");
    }
}
