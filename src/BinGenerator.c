#include "BinGenerator.h"

#include <stdio.h>
#include <stdlib.h>

#include "Memory.h"

void WriteBin(const char* asmFile, const char* binFile) {
    char command[256];

    snprintf(command, sizeof(command), "64tass %s -o %s", asmFile, binFile);
    int ret = system(command);

    if(ret != 0) {
        printf("Error: Failed to assemble %s\n", asmFile);
        return;
    }

    printf("Binary file successfully created\n");
}

void LoadBin(const char* binFile, const uint16_t baseAddr) {
    FILE* file = fopen(binFile, "rb");
    if(!file) return;

    uint8_t byte;
    uint16_t addr = baseAddr - 0x2;

    while(fread(&byte, 1, 1, file) == 1)
        RAM[addr++] = byte;

    fclose(file);
}
