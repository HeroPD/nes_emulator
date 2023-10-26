#include <stdint.h>
#include <rom.h>

#ifndef BUS_H
#define BUS_H

typedef struct
{
    uint8_t * ram;
    Mapper * mapper;
} Bus;

void nesbus_clear(Bus * bus, int start, int size);
void nesbus_write(Bus * bus, uint16_t address, uint8_t data);
uint8_t nesbus_read(Bus * bus, uint16_t address);

#endif