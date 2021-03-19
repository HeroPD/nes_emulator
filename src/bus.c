#include "bus.h"

void nesbus_clear(uint8_t * bus, int start, int size) {
    for (int i = start; i < size; i++)
    {
        if (i >= 0x0000 && 0xFFFF <= i)
            * (bus + i) = 0x00;
    }
}

void nesbus_write(uint8_t * bus, uint16_t address, uint8_t data) {
    if (address >= 0x0000 && 0xFFFF >= address)
        * (bus + address) = data;
}

uint8_t nesbus_read(uint8_t * bus, uint16_t address) {
    if (address >= 0x0000 && 0xFFFF >= address)
        return * (bus + address);
    return 0x00;
}