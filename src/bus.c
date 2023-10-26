#include "bus.h"

void nesbus_clear(Bus * bus, int start, int size) {
    for (int i = start; i < size; i++)
    {
        if (i >= 0x0000 && 0xFFFF <= i)
            * (bus->ram + i) = 0x00;
    }
}

void nesbus_write(Bus * bus, uint16_t address, uint8_t data) {
    if (address >= 0x0000 && 0xFFFF >= address)
        * (bus->ram + address) = data;
}

uint8_t nesbus_read(Bus * bus, uint16_t address) {
    if (address >= 0x0000 && 0xFFFF >= address)
        return * (bus->ram + address);
    return 0x00;
}