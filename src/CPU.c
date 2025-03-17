#include "CPU.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Registers.h"
#include "Memory.h"
#include "Monitor.h"

const Meta TABLE[] = {
    {0xEA, NOP, NONE, NONE, 1}, // No Operation
    {0xA9, LDA, REG, IMM, 2},   // Load Accumulator with Immediate
    {0xAD, LDA, MEM, NONE, 3},  // Load Accumulator with Absolute
    {0x8D, STA, MEM, REG, 3},   // Store Accumulator to Memory
    {0xAA, TAX, REG, REG, 1},   // Transfer Accumulator to X
    {0xE8, INX, REG, NONE, 1},  // Increment X
    {0x69, ADC, REG, IMM, 2},   // Add with Carry
    {0x6D, ADC, MEM, NONE, 3},  // Add with Carry (Absolute)
    {0xE9, SBC, REG, IMM, 2},   // Subtract with Carry
    {0x29, AND, REG, IMM, 2},   // Logical AND with Immediate
    {0x09, ORA, REG, IMM, 2},   // Logical Inclusive OR with Immediate
    {0x4C, JMP, MEM, NONE, 3},  // Jump to Memory Address
    {0xD0, BNE, NONE, REL, 2},  // Branch if Not Equal (relative jump)
    {0xF0, BEQ, NONE, REL, 2},  // Branch if Equal (relative jump)
    {0x48, PHA, NONE, REG, 1},  // Push Accumulator
    {0x68, PLA, REG, NONE, 1},  // Pull Accumulator
    {0x08, PHP, NONE, REG, 1},  // Push Processor Status
    {0x60, RTS, NONE, NONE, 1}, // Return from Subroutine
    {0x00, BRK, NONE, NONE, 1}, // Force Interrupt
    {0x40, RTI, NONE, NONE, 1}, // Return from Interrupt
};

uint8_t A = 0;
uint8_t X = 0;
uint8_t Y = 0;
uint8_t P = 0x24;
uint8_t SP = 0xFD;
uint16_t PC = 0x8000;

void InitCPU() {
    A = 0;
    X = 0;
    Y = 0;
    P = 0x24;
    SP = 0xFD;

    uint8_t lo = RAM[0xFFFC];
    uint8_t hi = RAM[0xFFFD];

    PC = (hi << 8) | lo;
}

static int StepCPU() {
    uint8_t op = Fetch();
    Instruction* instr = Decode(op);

    if(!instr) {
        printf("Unknown opcode: 0x%02X at PC: 0x%04X\n", op, PC - 1);
        return 0;
    }

    Execute(instr);
    free(instr);
    return 1;
}

void RunCPU() {
    char command[16];

    while(1) {
        printf("\n>> ");
        fgets(command, sizeof(command), stdin);

        if(strncmp(command, "step", 4) == 0) {
            if(!StepCPU()) break;
            PrintRegisters();
        }

        else if(strncmp(command, "dump", 4) == 0) DumpMemory(0x8000, 0x8010);
        else if(strncmp(command, "reg", 3) == 0) PrintRegisters();
        else if(strncmp(command, "exit", 4) == 0) break;

        else printf("Commands: step, dump, reg, exit\n");
    }
}

uint8_t Fetch() {
    return RAM[PC++];
}

Instruction* Decode(const uint8_t op) {
    size_t tableSize = sizeof(TABLE) / sizeof(TABLE[0]);

    for(size_t i = 0; i < tableSize; ++i) {
        if(TABLE[i].Op == op) {
            Instruction* instr = malloc(sizeof(Instruction));
            instr->Op = op;
            instr->Type = TABLE[i].Type;
            instr->Dst.Type = TABLE[i].Dst;
            instr->Src.Type = TABLE[i].Src;
            instr->Size = TABLE[i].Size;
            return instr;
        }
    }
    return NULL;
}

void Execute(const Instruction* instr) {
    switch(instr->Type) {
    case NOP: break;
    case LDA:
        ProcessLDA(instr);
        break;
    case STA:
        ProcessSTA(instr);
        break;
    case TAX:
        ProcessTAX(instr);
        break;
    case INX:
        ProcessINX(instr);
        break;
    case ADC:
        ProcessADC(instr);
        break;
    case SBC:
        ProcessSBC(instr);
        break;
    case AND:
        ProcessAND(instr);
        break;
    case ORA:
        ProcessORA(instr);
        break;
    case JMP:
        ProcessJMP(instr);
        break;
    case BNE:
        ProcessBNE(instr);
        break;
    case BEQ:
        ProcessBEQ(instr);
        break;
    case PHA:
        ProcessPHA();
        break;
    case PLA:
        ProcessPLA();
        break;
    case PHP:
        ProcessPHP();
        break;
    case RTS:
        ProcessRTS();
        break;
    case BRK:
        ProcessBRK();
        exit(0);
    case RTI:
        ProcessRTI();
        break;
    default: break;
    }
}
