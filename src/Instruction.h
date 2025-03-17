#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdint.h>

typedef enum {
    NONE,
    REG,
    IMM,
    MEM,
    REL
} OpType;

typedef enum {
    NOP,
    LDA, STA, TAX, INX,
    ADC, SBC, AND, ORA,
    JMP, BNE, BEQ,
    PHA, PLA, PHP, PLP, RTS,
    BRK, RTI
} InstructionType;

typedef struct {
    uint8_t Op;           // opcode
    InstructionType Type; // Instruction type
    OpType Dst;           // destination operand type
    OpType Src;           // source operand type
    uint8_t Size;         // command size (byte count)
} Meta;

typedef struct {
    OpType Type;
    union {
        uint8_t Reg;       // REG: Register number
        uint16_t Imm;      // IMM: Immediate value
        uint16_t Addr;     // MEM: Memory address
    };
} Operand;

typedef struct {
    uint8_t Op;            // opcode
    InstructionType Type;  // Instruction type
    Operand Dst;           // Operand
    Operand Src;           // Operand
    uint8_t Size;          // byte length
} Instruction;

// Instruction funcs

// Fetch Operand Address
extern uint16_t FetchOpAddr(const OpType type);
extern uint8_t ReadOp(const OpType type, const uint16_t addr);

// Basic Instruction Processors
extern void ProcessLDA(const Instruction* instr);
extern void ProcessSTA(const Instruction* instr);
extern void ProcessTAX(const Instruction* instr);
extern void ProcessINX(const Instruction* instr);

// ALU Instruction Processors
extern void ProcessADC(const Instruction* instr);
extern void ProcessSBC(const Instruction* instr);
extern void ProcessAND(const Instruction* instr);
extern void ProcessORA(const Instruction* instr);

// Branch Instruction Processors
extern void ProcessJMP(const Instruction* instr);
extern void ProcessBNE(const Instruction* instr);
extern void ProcessBEQ(const Instruction* instr);

// Stack Instruction Processors
extern void ProcessPHA();
extern void ProcessPLA();
extern void ProcessPHP();
extern void ProcessPLP();
extern void ProcessRTS();

// Interrupt Instruction Processors
extern void ProcessBRK();
extern void ProcessRTI();

#endif
