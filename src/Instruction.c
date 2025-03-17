#include "Instruction.h"

#include "Memory.h"
#include "Registers.h"
#include "Flags.h"

#include "IO.h"

uint16_t FetchOpAddr(const OpType type) {
    switch(type) {
    case IMM:
        return PC++;
    case MEM: {
        uint8_t lo = RAM[PC++];
        uint8_t hi = RAM[PC++];
        return (hi << 8) | lo;
    }
    case REL: {
        int8_t offset = (int8_t)RAM[PC++];
        return PC + offset;
    }
    case REG:
    case NONE:
    default: return 0;
    }
}

uint8_t ReadOp(const OpType type, const uint16_t addr) {
    switch(type) {
    case IMM:
    case MEM:
    case REL:
        return RAM[addr];
    case REG:
        return A;
    default:
        return 0;
    }
}

void ProcessLDA(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    uint8_t value = ReadOp(instr->Src.Type, addr);
    A = value;
    SetZNFlags(A);
}

void ProcessSTA(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Dst.Type);
    WriteMemory(addr, A);
}

void ProcessTAX(const Instruction* instr) {
    X = A;
    SetZNFlags(X);
}

void ProcessINX(const Instruction* instr) {
    X++;
    SetZNFlags(X);
}

void ProcessADC(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    uint8_t value = ReadOp(instr->Src.Type, addr);
    uint16_t sum = A + value + (P & C ? 1 : 0);

    SetFlag(C, sum > 0xFF);
    SetFlag(Z, (sum & 0xFF) == 0);
    SetFlag(N, sum & 0x80);

    A = sum & 0xFF;
}

void ProcessSBC(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    uint8_t value = ReadOp(instr->Src.Type, addr);
    uint16_t diff = A - value - (P & C ? 1 : 0);

    SetFlag(C, diff <= 0xFF);
    SetFlag(Z, (diff & 0xFF) == 0);
    SetFlag(N, diff & 0x80);

    A = diff & 0xFF;
}

void ProcessAND(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    uint8_t value = ReadOp(instr->Src.Type, addr);

    A = A & value;
    SetZNFlags(A);
}

void ProcessORA(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    uint8_t value = ReadOp(instr->Src.Type, addr);

    A = A | value;
    SetZNFlags(A);
}

void ProcessJMP(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    PC = addr;
}

void ProcessBNE(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    PC = !(P & Z) ? addr : PC;
}

void ProcessBEQ(const Instruction* instr) {
    uint16_t addr = FetchOpAddr(instr->Src.Type);
    PC = P & Z ? addr : PC;
}

void ProcessPHA() {
    RAM[0x0100 + SP] = A;
    --SP;
}

void ProcessPLA() {
    ++SP;
    A = RAM[0x0100 + SP];
    SetZNFlags(A);
}

void ProcessPHP() {
    RAM[0x0100 + SP] = P | B | U;
    --SP;
}

void ProcessPLP() {
    ++SP;
    P = RAM[0x0100 + SP];
    P |= U;
}

void ProcessRTS() {
    SP++;
    uint8_t lo = RAM[0x0100 + SP];

    SP++;
    uint8_t hi = RAM[0x0100 + SP];

    uint16_t addr = (hi << 8) | lo;
    PC = addr + 1;
}

void ProcessBRK() {
    uint16_t addr = PC + 1;

    RAM[0x0100 + SP--] = (addr >> 8) & 0xFF;
    RAM[0x0100 + SP--] = addr & 0xFF;
    RAM[0x0100 + SP--] = P | B | U;

    uint8_t lo = RAM[0xFFFE];
    uint8_t hi = RAM[0xFFFF];

    PC = (hi << 8) | lo;
    SetFlag(I, 1);
}

void ProcessRTI() {
    SP++;
    P = RAM[0x0100 + SP];
    P |= U;

    SP++;
    uint8_t lo = RAM[0x0100 + SP];

    SP++;
    uint8_t hi = RAM[0x0100 + SP];

    PC = (hi << 8) | lo;
}
