#ifndef BIN_GENERATOR_H
#define BIN_GENERATOR_H

#include <stdint.h>

void WriteBin(const char* asmFile, const char* binFile);
void LoadBin(const char* binFile, const uint16_t baseAddr);

#endif
