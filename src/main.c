#include "CPU.h"
#include "Memory.h"
#include "BinGenerator.h"

#define ASM_FILE "/Users/g1/Desktop/G1/study/cpu/data/prog.asm"
#define BIN_FILE "/Users/g1/Desktop/G1/study/cpu/data/prog.bin"

uint8_t RAM[MEMORY_SIZE] = {0};

void Init() {
    WriteBin(ASM_FILE, BIN_FILE);
    LoadBin(BIN_FILE, 0x8000);

    RAM[0xFFFC] = 0x00;
    RAM[0xFFFD] = 0x80;

    InitCPU();
}

int main(int argc, char *argv[]) {
    Init();
    RunCPU();
    return 0;
}
