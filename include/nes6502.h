#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include "stdbool.h"
#include "bus.h"

typedef struct
{
    uint8_t a;
    uint8_t x;
    uint8_t y;
    uint8_t sp;
    uint16_t pc;
    uint8_t status;
    uint16_t abs_addr;
    uint16_t rel_addr;
    /* data */
} cpu6502;

typedef enum {
    N = 1 << 7,
    V = 1 << 6,
    U = 1 << 5,
    B = 1 << 4,
    D = 1 << 3,
    I = 1 << 2,
    Z = 1 << 1,
    C = 1 << 0
} StatusType;

cpu6502 init_state();

void set_status(cpu6502 * state, StatusType type, bool value);
bool check_status(cpu6502 * state, StatusType type);

void reset(cpu6502 state);
void irq(cpu6502 state);
void nmi(cpu6502 state);
void nes_clock(cpu6502 * state, Bus * bus);

void load_code(Bus * bus, cpu6502 state, uint8_t code [], int code_size);
