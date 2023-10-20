#include <stdio.h>
#include <stdlib.h>

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