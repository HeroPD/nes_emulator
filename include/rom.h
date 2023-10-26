#include <stdio.h>
#include <stdlib.h>

#ifndef ROM_H
#define ROM_H

typedef struct
{
    int mapper;
    uint16_t prg_start;
    uint16_t prg_end;
    uint8_t* prg;
    int prg_len;
    uint8_t* chr;
    int chr_len;
} Mapper;

Mapper* load_rom(const char* filename, size_t* length);
uint8_t read_prg(Mapper *mapper, uint16_t address);
void free_rom(Mapper *mapper);

#endif