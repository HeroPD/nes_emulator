#include <stdint.h>

void nesbus_clear(uint8_t * bus, int start, int size);
void nesbus_write(uint8_t * bus, uint16_t address, uint8_t data);
uint8_t nesbus_read(uint8_t * bus, uint16_t address);
