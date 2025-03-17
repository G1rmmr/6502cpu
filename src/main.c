#include <stdio.h>

#include "CPU.h"
#include "Memory.h"

#define PROGRAM_NAME "/Users/g1/Desktop/G1/study/cpu/data/prog.bin"

uint8_t RAM[MEMORY_SIZE] = {0};

void WriteBin(const char* binFile) {
    FILE* file = fopen(binFile, "wb");
    if(!file) return;

    uint8_t program[] = {
        0xA9, 0x41,       // LDA #$41
        0x8D, 0x01, 0x80, // STA $8001
        0x00              // BRK
    };

    size_t size = sizeof(program);
    size_t written = fwrite(program, 1, size, file);
    fclose(file);

    if(written != size) return;
}

void LoadBin(const char* binFile, const uint16_t baseAddr) {
    FILE* file = fopen(binFile, "rb");
    if(!file) return;

    uint8_t byte;
    uint16_t addr = baseAddr;

    while(fread(&byte, 1, 1, file) == 1)
        RAM[addr++] = byte;

    fclose(file);
}

int main(int argc, char *argv[]) {
    WriteBin(PROGRAM_NAME);
    LoadBin(PROGRAM_NAME, 0x8000);

    printf("Loaded RAM[0x8000..0x8005]: ");
    for (int i = 0; i < 6; ++i)
        printf("%02X ", RAM[0x8000 + i]);
    printf("\n");

    RAM[0xFFFC] = 0x00;
    RAM[0xFFFD] = 0x80;

    InitCPU();
    RunCPU();
    return 0;
}
